#include "s21_string.h"

int s21_sscanf(const char* buffer, const char* format, ...) {
  int count = 0, check;
  const char* buf_n = buffer;
  set_format settings = {0, 0, 0};
  va_list factor;              // указатель va_list
  va_start(factor, *format);   // устанавливаем указатель
  for (; *format; format++) {  // идем по строке формата
    if (*format == '%' &&
        *(format - 1) != '%') {  // после процента смотрим формат
      format++;
      settings.astra =
          asterisk(&format);  // проверка на звезду. звездочка подавляет текущее
                              // записывание информации в перемнную
      settings.width = width_define_s(&format);  // определяем ширину. какой
                                                 // длины будет строка или число
      settings.length =
          length_define(&format);  // определяем длину (long, short)
      check = formats_s(&buffer, &format, factor, &buf_n,
                        settings);  // идем к форматам
      if (check)
        count++;
      else if (!settings.astra)
        break;  // если считывание или запись в перемнную провалены - кирдык. но
                // звездочка не считается
    } else if (*format == *buffer)
      buffer++;
    else if (*buffer == ' ' || *buffer == '\n' || *buffer == '\t')
      buffer++;
  }
  va_end(factor);  // завершаем вот эту вот va
  return count;
}

int asterisk(const char** format) {
  int res = 0;
  if (**format == '*') {
    *format += 1;
    res = 1;
  }
  return res;
}

int width_define_s(const char** format) {
  long int num = 0;
  set_format nulls = {0, 0, 0};
  num_d(format, &num, 10, nulls);
  return num;
}

int formats_s(const char** buffer, const char** format, va_list factor,
              const char** buf_n, set_format settings) {
  int check = 0;
  if (**format == 'c') {
    check = format_c(buffer, factor, settings);
  }
  if (**format == 'd') {
    check = format_d(buffer, factor, settings);
  }
  if (**format == 's') {
    check = format_s(buffer, factor, settings);
  }
  if (**format == 'f') {
    check = format_ef(buffer, factor, settings, 0);
  }
  if (**format == 'n') {  // количество считанных символов из буффера
    long int num = *buffer - *buf_n;
    d_memory_s(factor, num, settings.length);
  }
  if (**format == 'o') {
    check = format_o(buffer, factor, settings);
  }
  if (**format == 'u') {
    check = format_u(buffer, factor, settings);
  }
  if (**format == 'x' || **format == 'X') {
    check = format_x(buffer, factor, settings);
  }
  if (**format == 'i') {
    check = format_i(buffer, factor, settings);
  }
  if (**format == 'p') {
    check = format_p(buffer, factor, settings);
  }
  if (**format == 'e' || **format == 'E') {
    check = format_ef(buffer, factor, settings, 0);
  }
  if (**format == 'g') {
    check = format_ef(buffer, factor, settings, 1);
  }
  return check;
}

int format_c(const char** buffer, va_list factor, set_format settings) {
  int check = 0;
  if (!settings.astra) {
    void** value = va_arg(factor, void*);
    *(char*)value = **buffer;
    check = 1;
  }
  *buffer += 1;
  return check;
}

int format_s(const char** buffer, va_list factor, set_format settings) {
  int check = 0;
  char str[1024];
  if (**buffer != '\0') {
    get_str(buffer, str, settings);
    check = 1;
  }
  if (check && !settings.astra) {
    void** value = va_arg(factor, void*);
    s21_strncpy((char*)value, str, s21_strlen(str));
    *((char*)value + s21_strlen(str)) = '\0';
    check = 1;
  } else
    check = 0;
  return check;
}

int format_p(const char** buffer, va_list factor, set_format settings) {
  unsigned long int num = 0;
  int check =
      num_x(buffer, &num, settings);  // считываем число в 16-ричной системе
  if (check && !settings.astra) {
    void** value = va_arg(factor, void*);
    *value = (void*)num;  // меняем адрес указателя
  } else
    check = 0;
  return check;
}

int format_x(const char** buffer, va_list factor, set_format settings) {
  unsigned long int num = 0;
  int check = num_x(buffer, &num, settings);
  if (check && !settings.astra)
    u_memory_s(factor, num, settings.length);
  else
    check = 0;
  return check;
}

int format_i(const char** buffer, va_list factor, set_format settings) {
  int check = 0;
  if (**buffer == '0') {
    *buffer += 1;
    if (**buffer == 'x' || **buffer == 'X') {
      *buffer += 1;
      check = format_x(buffer, factor, settings);
    } else
      check = format_o(buffer, factor, settings);
  } else
    check = format_d(buffer, factor, settings);
  return check;
}

int format_d(const char** buffer, va_list factor, set_format settings) {
  long int num = 0;
  int check = num_d(buffer, &num, 10, settings);
  if (check && !settings.astra)
    d_memory_s(factor, num, settings.length);
  else
    check = 0;
  return check;
}

int format_o(const char** buffer, va_list factor, set_format settings) {
  long int num = 0;
  int check = num_d(buffer, &num, 8, settings);
  if (check && !settings.astra)
    u_memory_s(factor, num, settings.length);
  else
    check = 0;
  return check;
}

int format_u(const char** buffer, va_list factor, set_format settings) {
  long int num = 0;
  int check = num_d(buffer, &num, 10, settings);
  if (check && !settings.astra)
    u_memory_s(factor, num, settings.length);
  else
    check = 0;
  return check;
}

int format_ef(const char** buffer, va_list factor, set_format settings,
              int format_g) {
  long int num = 0;
  long double float_num = 0;
  int check = num_d(buffer, &num, 10, settings);
  float_num = num;
  num_f(buffer, &float_num, settings);
  if ((format_g && **buffer == 'e') || (!format_g && **buffer == 'e')) {
    *buffer += 1;
    num = 0;
    if (num_d(buffer, &num, 10, settings))
      float_num *= pow(10, num);
    else
      *buffer -= 1;
  }
  if (check && !settings.astra)
    f_memory_s(factor, float_num, settings.length);
  else
    check = 0;
  return check;
}

void d_memory_s(va_list factor, long int num, char length) {
  if (length == 'l') {
    long int* value = va_arg(factor, long int*);
    *value = (long int)num;
  } else if (length == 'h') {
    short* value = va_arg(factor, short*);
    *value = (short)num;
  } else {
    int* value = va_arg(factor, int*);
    *value = (int)num;
  }
}

void u_memory_s(va_list factor, long int num, char length) {
  if (length == 'l') {
    unsigned long int* value = va_arg(factor, unsigned long int*);
    *value = (unsigned long int)num;
  } else if (length == 'h') {
    unsigned short* value = va_arg(factor, unsigned short*);
    *value = (unsigned short)num;
  } else {
    unsigned int* value = va_arg(factor, unsigned int*);
    *value = (unsigned int)num;
  }
}

void f_memory_s(va_list factor, long double num, char length) {
  if (length == 'L') {
    long double* value = va_arg(factor, long double*);
    *value = (long double)num;
  } else if (length == 'l') {
    double* value = va_arg(factor, double*);
    *value = (double)num;
  } else {
    float* value = va_arg(factor, float*);
    *value = (float)num;
  }
}

int num_d(const char** buffer, long int* num, int sys, set_format settings) {
  int minus = 0, check = 0;
  if (*num == 0) {
    if (**buffer == '-') {
      minus = 1;
      *buffer += 1;
    } else if (**buffer == '+')
      *buffer += 1;
    for (int i = 1; **buffer >= '0' && **buffer <= '0' + sys;
         i++, *buffer += 1) {
      check = 1;
      *num = *num * sys + (**buffer - '0');
      if (settings.width && i == settings.width) break;
    }
    if (minus) *num *= -1;
  }
  return check;
}

void num_f(const char** buffer, long double* float_num, set_format settings) {
  double num = 0;
  if (**buffer == '.') {
    *buffer += 1;
    for (int i = 1; **buffer >= '0' && **buffer <= '9'; i++, *buffer += 1) {
      double digit = (**buffer - '0');
      digit = round(digit);
      num += digit * pow(10, -i);
      if (settings.width && i == settings.width) break;
    }
  }
  *float_num += num;
}

int num_x(const char** buffer, unsigned long int* num, set_format settings) {
  int check = 0, minus = 0;
  if (**buffer == '-') {
    *buffer += 1;
    minus = 1;
  }
  int i = 1;
  for (; (**buffer >= '0' && **buffer <= '9') ||
         (**buffer >= 'A' && **buffer <= 'F') ||
         (**buffer >= 'a' && **buffer <= 'f');
       i++, *buffer += 1) {
    check = 1;
    int x;
    if (**buffer >= '0' && **buffer <= '9') x = **buffer - 48;
    if (**buffer >= 'A' && **buffer <= 'Z') x = **buffer - 55;
    if (**buffer >= 'a' && **buffer <= 'z') x = **buffer - 87;
    *num = *num * 16 + x;
    if (settings.width && i == settings.width) break;
  }
  if (i > 18) {
    *num = 0;
    const char* big_num = "fffffffffffffffff";
    check = num_x(&big_num, num, settings);
  }
  if (minus) *num *= -1;
  return check;
}

void get_str(const char** buffer, char* str, set_format settings) {
  int i = 0;
  while (**buffer != ' ' && **buffer != '\n' && **buffer != '\t' &&
         **buffer != '\0') {
    *str = **buffer;
    *buffer += 1;
    str++;
    i++;
    if (settings.width && i == settings.width) break;
  }
  *str = '\0';
}
