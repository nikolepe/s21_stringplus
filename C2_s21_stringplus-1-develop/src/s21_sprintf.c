#include "s21_string.h"

int s21_sprintf(char* buffer, const char* format, ...) {
  char* buf_n = buffer;
  va_list factor;
  va_start(factor, *format);
  for (; *format; format++) {
    set_format1 settings = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (*format == '%') {
      format++;
      flag_define(&format, &settings);
      settings.width = width_define_p(&format, factor);
      accuracy_define(&format, factor, &settings);
      settings.length = length_define(&format);
      formats_p(&buffer, &format, factor, settings, &buf_n);
    } else {
      *buffer = *format;
      buffer++;
    }
  }
  va_end(factor);
  *buffer = '\0';
  return buffer - buf_n;
}

// тут ифы или елс ифы
void flag_define(const char** format, set_format1* settings) {
  while (s21_strchr("+- #0", **format)) {
    if (**format == '+') {
      settings->flag_plus = 1;
      *format += 1;
    }
    if (**format == '-') {
      settings->flag_dash = 1;
      *format += 1;
    }
    if (**format == ' ') {
      settings->flag_space = 1;
      *format += 1;
    }
    if (**format == '#') {
      settings->flag_diez = 1;
      *format += 1;
    }
    if (**format == '0') {
      settings->flag_0 = 1;
      *format += 1;
    }
  }
}

int width_define_p(const char** format, va_list factor) {
  int res = 0;
  if (**format == '*') {
    // если звездочка то ширину берем из аргумента функции
    res = va_arg(factor, int);
    *format += 1;
  } else if (**format != '.') {
    res = atoi(*format);
    if (res) {
      while (isdigit(**format)) *format += 1;
    }
  }
  return res;
}

void accuracy_define(const char** format, va_list factor,
                     set_format1* settings) {
  settings->accur_int = -1;
  if (**format == '.') {
    *format += 1;
    settings->accur = atoi(*format);
    settings->accur_int = atoi(*format);
    while (isdigit(**format)) *format += 1;
  } else
    settings->accur = 6;
  if (**format == '*') {
    settings->accur = va_arg(factor, int);
    settings->accur_int = settings->accur;
    *format += 1;
  }
}

void formats_p(char** buffer, const char** format, va_list factor,
               set_format1 settings, char** buf_n) {
  // классификация по системам счисления
  if (s21_strchr("dufeEigG", **format)) settings.sys = 10;
  if (s21_strchr("Xxp", **format)) settings.sys = 16;
  if (**format == 'o') settings.sys = 8;
  if (s21_strchr("XEG", **format)) settings.reg = 1;
  if (**format == 'c') {
    c_format(buffer, factor, settings);
  } else if (**format == 'd' || **format == 'i') {
    d_format(buffer, factor, settings);
  } else if (**format == 's') {
    s_format(buffer, factor, settings);
  } else if (**format == 'u' || **format == 'o' || **format == 'x' ||
             **format == 'X') {
    u_format(buffer, factor, settings);
  } else if (**format == 'f') {
    ef_format(buffer, factor, settings, 'f');
  } else if (**format == 'n') {
    // количество считанных символов из буффера
    long int num = *buffer - *buf_n;
    int* value = va_arg(factor, int*);
    *value = (int)num;
  } else if (**format == 'p') {
    p_format(buffer, factor, settings);
  } else if (**format == 'e' || **format == 'E') {
    ef_format(buffer, factor, settings, 'e');
  } else if (**format == 'g' || **format == 'G') {
    ef_format(buffer, factor, settings, 'g');
  } else if (**format == '%') {
    **buffer = **format;
    *buffer += 1;
    **buffer = '\0';
  }
}

void reverse_str(char* str) {
  char result[20];
  for (int i = (int)s21_strlen(str) - 1, j = 0; i >= 0; j++, i--) {
    result[j] = str[i];
    result[j + 1] = '\0';
  }
  s21_strncpy(str, result, 20);
}

void num_to_str(long int num, char* str_num, set_format1 settings) {
  // сначала записали по одной цифре в строку
  int i = 0;
  for (; num; num /= settings.sys, i++) {
    int ost = num % settings.sys;
    if (settings.sys == 16 && ost >= 10) {
      // в 16-ричной после 9 идут abcdef
      if (settings.reg)
        // если Х
        str_num[i] = ost + 55;
      else
        // если х
        str_num[i] = ost + 87;
    } else
      str_num[i] = num % settings.sys + '0';
  }
  if (!i) {
    str_num[i] = '0';
    i++;
  }
  str_num[i] = '\0';
  // потом перевернули
  reverse_str(str_num);
}

void c_format(char** buffer, va_list factor, set_format1 settings) {
  char c = (char)va_arg(factor, int);
  if (!settings.flag_dash) expand(buffer, settings, 1, ' ');
  **buffer = c;
  *buffer += 1;
  if (settings.flag_dash) expand(buffer, settings, 1, ' ');
  **buffer = '\0';
}

void s_format(char** buffer, va_list factor, set_format1 settings) {
  char* str = va_arg(factor, char*);
  int size = s21_strlen(str);
  if (settings.accur_int >= 0 && settings.accur_int < size)
    size = settings.accur_int;
  // если была указана ширина, заполняем недостающее пробелами
  if (!settings.flag_dash) expand(buffer, settings, size, ' ');
  if (size > 0) {
    // копируем строку в буфер
    s21_strncpy(*buffer, str, size);
    *buffer += size;
  }
  if (settings.flag_dash) expand(buffer, settings, size, ' ');
  **buffer = '\0';
}

void d_format(char** buffer, va_list factor, set_format1 settings) {
  long int num = 0;
  d_memory_p(&num, factor, settings);
  char sign = '\0';
  int_sign_and_width(num, &sign, &settings);
  width_accur(&settings);
  if (sign == '-') num *= -1;
  char num_str[50] = "";
  if (settings.accur_int || num) num_to_str(num, num_str, settings);
  int size = (int)s21_strlen(num_str);
  if (settings.accur_int > size) size = settings.accur_int;
  char wid = ' ';
  if (settings.flag_0) {
    wid = '0';
    if (sign) {
      **buffer = sign;
      *buffer += 1;
    }
  }
  if (!settings.flag_dash) expand(buffer, settings, size, wid);
  if (settings.flag_dash && settings.flag_0) {
    wid = ' ';
  }
  if (!settings.flag_0 && sign) {
    **buffer = sign;
    *buffer += 1;
  }
  for (int i = size; i > (int)s21_strlen(num_str); i--) {
    **buffer = '0';
    *buffer += 1;
  }
  s21_strncpy(*buffer, num_str, 50);
  *buffer += (int)s21_strlen(num_str);
  if (settings.flag_dash) expand(buffer, settings, size, wid);
}

void p_format(char** buffer, va_list factor, set_format1 settings) {
  void** value = va_arg(factor, void*);
  if (value) {
    char string[50] = "";
    num_to_str((long int)value, string, settings);
    settings.width -= 2;
    int size = (int)s21_strlen(string);
    if (!settings.flag_dash) expand(buffer, settings, size, ' ');
    s21_strncpy(*buffer, "0x", 3);
    *buffer += 2;
    s21_strncpy(*buffer, string, s21_strlen(string));
    *buffer += s21_strlen(string);
    if (settings.flag_dash) expand(buffer, settings, size, ' ');
    **buffer = '\0';
  } else {
    s21_strncpy(*buffer, "(nil)", 5);
    *buffer += 5;
  }
}

void u_format(char** buffer, va_list factor, set_format1 settings) {
  unsigned long int num = 0;
  int size = 0;
  u_memory_p(&num, factor, settings);
  width_accur(&settings);
  char num_str[50] = "";
  num_to_str(num, num_str, settings);
  size = (int)s21_strlen(num_str);
  if (settings.accur_int > size) size = settings.accur_int;
  if (num && settings.flag_diez) {
    diez_edit_width(&settings);
  }
  char wid = ' ';
  if (settings.flag_0) wid = '0';
  if (!settings.flag_dash) expand(buffer, settings, size, wid);
  if (settings.flag_diez && num) {
    diez_uns_add(buffer, settings);
  }
  for (int i = size; i > (int)s21_strlen(num_str); i--) {
    **buffer = '0';
    *buffer += 1;
  }
  s21_strncpy(*buffer, num_str, 50);
  *buffer += (int)s21_strlen(num_str);
  if (settings.flag_dash) expand(buffer, settings, size, wid);
}

void ef_format(char** buffer, va_list factor, set_format1 settings, char ga) {
  char e_num_str[50] = "", float_str[50] = "", num_str[50] = "";
  char sign = '\0', wid = ' ';
  int flag_delete = 0, size = 0;
  long double num = 0;
  f_memory_p(&num, factor, settings);
  if (ga == 'g') {
    g_accur(num, &settings, &ga);
    flag_delete = 1;
    if (!settings.accur) settings.accur++;
    if (!num) settings.accur = 0;
  }
  if (!settings.accur) num = round(num);
  int_sign_and_width(num, &sign, &settings);
  if (sign == '-') num *= -1;
  exp_to_str(num, e_num_str, settings, flag_delete);
  float_to_str(num, float_str, settings);
  if (edit_float(float_str)) num++;
  num_to_str(num, num_str, settings);
  if (flag_delete && !settings.flag_diez) delete_extra(float_str, &settings);
  if (ga == 'f') size = s21_strlen(num_str) + s21_strlen(float_str) + 1;
  if (ga == 'e') {
    size = s21_strlen(e_num_str);
    s21_strncpy(num_str, e_num_str, size);
    num_str[size] = '\0';
  }
  if (settings.flag_0) {
    wid = '0';
    if (sign) {
      **buffer = sign;
      *buffer += 1;
    }
  }
  if (!settings.flag_dash) expand(buffer, settings, size, wid);
  if (!settings.flag_0 && sign) {
    **buffer = sign;
    *buffer += 1;
  }
  s21_strncpy(*buffer, num_str, 50);
  *buffer += s21_strlen(num_str);
  if (ga == 'f') {
    if (settings.accur || settings.flag_diez) {
      **buffer = '.';
      *buffer += 1;
    }
    s21_strncpy(*buffer, float_str, 50);
    *buffer += s21_strlen(float_str);
  }
  if (settings.flag_dash) expand(buffer, settings, size, wid);
}

void exp_to_str(long double num, char* num_str, set_format1 settings,
                int flag_delete) {
  char temp[50] = "";
  int sign = 0;
  if (num > 1 || !num) sign = 1;
  int step = 0;
  if (num) {
    for (; !(num < 10 && num >= 1); step++)
      if (sign)
        num /= 10;
      else
        num *= 10;
  }
  char float_str[50] = "";
  float_to_str(num, float_str, settings);
  if (edit_float(float_str)) {
    if (!(num - round(num))) num++;
    if (round(num) >= 10) {
      num /= 10;
      step--;
    }
  }

  if (flag_delete && !settings.flag_diez) delete_extra(float_str, &settings);
  int index = 0;
  if (settings.accur) {
    temp[index++] = (int)num + '0';
    temp[index++] = '.';
  } else
    temp[index++] = round(num) + '0';
  temp[index] = '\0';
  s21_strncat(temp, float_str, s21_strlen(float_str));
  index += s21_strlen(float_str);
  if (settings.reg)
    temp[index++] = 'E';
  else
    temp[index++] = 'e';
  if (sign)
    temp[index++] = '+';
  else
    temp[index++] = '-';
  if (step < 10) {
    temp[index++] = '0';
    temp[index++] = step + '0';
    temp[index] = '\0';
  } else {
    temp[index] = '\0';
    char step_str[100];
    num_to_str(step, step_str, settings);
    s21_strncat(temp, step_str, s21_strlen(step_str));
  }
  s21_strncpy(num_str, temp, s21_strlen(temp));
}

void float_to_str(long double num, char* num_str, set_format1 settings) {
  num -= (long)num;
  for (int i = 0; i < settings.accur; i++) {
    num *= 10;
    if (settings.accur - i == 1) {
      num_str[i] = round(num) + '0';
    } else
      num_str[i] = (int)num + '0';
    num -= (int)num;
    num_str[i + 1] = '\0';
  }
  if (!settings.accur) *num_str = '\0';
}

int edit_float(char* float_str) {
  int res = 0;
  if (float_str != s21_NULL) {
    int i = s21_strlen(float_str) - 1;
    for (; float_str[i] == ':' && i >= 0; i--) {
      float_str[i] = '0';
      if (i >= 1)
        float_str[i - 1] += 1;
      else {
        res = 1;
        break;
      }
    }
  }
  return res;
}

void int_sign_and_width(long double num, char* sign, set_format1* settings) {
  if (settings->width < 0) {
    settings->width *= -1;
    settings->flag_dash = 1;
  }
  if (num < 0) {
    *sign = '-';
    settings->width -= 1;  // чтобы не выводились лишние пробелы/нули
  } else if (num > 0 && settings->flag_plus) {
    *sign = '+';
    settings->width -= 1;
  }
  if (*sign != '-' && settings->flag_space)
    *sign = ' ';  // при флаге пробел если нет знака минус ставим пробел
}

void d_memory_p(long int* num, va_list factor, set_format1 settings) {
  *num = va_arg(factor, long int);
  if (settings.length == 'h')
    *num = (short)*num;
  else if (settings.length != 'l')
    *num = (int)*num;
  if (!inf_or_nan(*num)) {
    exit(1);
  }
}

void u_memory_p(unsigned long int* num, va_list factor, set_format1 settings) {
  *num = va_arg(factor, unsigned long int);
  if (settings.length == 'h')
    *num = (unsigned short)*num;
  else if (settings.length != 'l')
    *num = (unsigned int)*num;
  if (!inf_or_nan(*num)) {
    exit(1);
  }
}

void f_memory_p(long double* num, va_list factor, set_format1 settings) {
  if (settings.length == 'L')
    *num = va_arg(factor, long double);
  else {
    *num = va_arg(factor, double);
  }
  if (!inf_or_nan(*num)) {
    exit(1);
  }
}

void expand(char** buffer, set_format1 settings, int size, char wid) {
  for (int i = size; i < settings.width; i++) {
    **buffer = wid;
    *buffer += 1;
  }
}

void diez_edit_width(set_format1* settings) {
  if (settings->sys == 16) settings->width -= 2;
  if (settings->sys == 8) settings->width -= 1;
}

void diez_uns_add(char** buffer, set_format1 settings) {
  **buffer = '0';
  *buffer += 1;
  if (settings.sys == 16) {
    if (settings.reg)
      **buffer = 'X';
    else
      **buffer = 'x';
    *buffer += 1;
  }
}

void g_accur(long double num, set_format1* settings, char* ga) {
  int log = (int)floorl(log10l(num));
  int len = 0;
  long int num_copy = num;
  for (; num_copy; num_copy /= 10, len++)
    ;
  if (num && log < -4) {
    *ga = 'e';
  } else {
    if (len == settings->accur) {
      settings->accur = len;
      *ga = 'f';
    } else if (len > settings->accur) {
      if (settings->accur) settings->accur--;
      *ga = 'e';
    } else {
      settings->accur -= len;
      *ga = 'f';
    }
  }
}

void delete_extra(char* str, set_format1* settings) {
  str += (int)s21_strlen(str) - 1;
  for (; *str == '0'; str--, settings->accur--) *str = '\0';
}

int inf_or_nan(long double num) {
  int res = 1;
  if (isinf(num) || isnan(num)) res = 0;
  return res;
}

void width_accur(set_format1* settings) {
  if (settings->accur_int > 0) {
    if (settings->accur_int > settings->width) {
      settings->width = settings->accur_int;
    }
  }
}