#include "s21_string.h"

// Поиск первого вхождения символа 'c' в строке 'str'
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *str_ptr = (const unsigned char *)
      str;  // Приведение типа void* к const unsigned char*
  void *res = s21_NULL;  // Инициализация result значением NULL
  s21_size_t i = 0;  // Инициализация счетчика обработанных байт

  while (i < n && res == s21_NULL) {
    // Цикл по символам строки 'str' до достижения
    // длины 'n' или нахождения искомого символа
    if (str_ptr[i] == c) {  // Проверка на совпадение символа
      res = (void *)&str_ptr[i];  // Сохраняем указатель на найденный символ
    }
    i++;  // Увеличение счетчика обработанных байт
  }
  return res;  // Возвращение указателя на найденный символ или NULL
}

// Лексикографическое сравнение двух блоков памяти
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;
  int res = 0;
  s21_size_t i = 0;

  while (i < n && res == 0) {  // Цикл по байтам до длины 'n' или различия
    if (s1[i] != s2[i]) {  // Проверка на различие байтов
      res = s1[i] - s2[i];  // Вычисляем разницу между байтами
    }
    i++;
  }
  return res;
}

// Копирование блока памяти
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *d = (char *)dest;
  const char *s = (const char *)src;
  s21_size_t i = 0;

  while (i < n) {  // Цикл по байтам до достижения длины 'n'
    d[i] = s[i];  // Копируем байт из исходного блока в целевой
    i++;
  }
  return dest;  // Возвращение указателя на начало целевого блока памяти
}

// Заполнение блока памяти заданным значением
void *s21_memset(void *dest, int c, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  s21_size_t i = 0;

  while (i < n) {
    d[i] = (unsigned char)c;  // Заполняем текущий байт значением 'c'
    i++;
  }
  return dest;  // Возвращение указателя на начало заполненного блока памяти
}

// Присоединение строки 'src' к строке 'dest' с ограничением по длине
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *dest_end = dest + s21_strlen(dest);  // Указатель на конец строки 'dest'
  s21_size_t i = 0;

  while (i < n && src[i] != '\0') {  // Цикл копирования символов
    *dest_end++ = src[i++];  // Копируем символ, увеличиваем индексы
  }
  *dest_end = '\0';  // Добавляем нуль-терминатор
  return dest;  // Возвращаем указатель на начало строки
}

// Поиск первого вхождения символа 'c' в строке 'str'
char *s21_strchr(const char *str, int c) {
  char *res = s21_NULL;
  s21_size_t i = 0;

  while (str[i] != '\0' && res == s21_NULL) {
    // Цикл до конца строки или нахождения символа
    if (str[i] == c) {  // Проверяем на совпадение
      res = (char *)&str[i];  // Сохраняем указатель на найденный символ
    }
    i++;
  }
  // Если искомый символ - терминированный нуль, то необходимо вернуть указатель
  // на него в строке 'str'
  if (str[i] == '\0' && res == s21_NULL && c == '\0') {
    res = (char *)&str[i];
  }
  return res;  // Возвращаем указатель или NULL
}

// Лексикографическое сравнение двух строк с ограничением по длине
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  // str1 и str2 не NULL
  if (str1 && str2 && n != 0) {
    for (s21_size_t i = 0; i < n; i++) {
      // Если в первой строке терминальный нуль или не равные символы
      // то берем разницу, выходим
      if (str1[i] == '\0' || str1[i] != str2[i]) {
        res = str1[i] - str2[i];
        break;
      }
    }
  }
  return res;
}

// Копирование строки 'src' в строку 'dest' с ограничением по длине
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;

  while (i < n) {  // Цикл копирования символов до длины 'n'
    dest[i] = src[i];  // Копируем символ
    if (src[i] == '\0') {
      while (i < n) {
        // Заполняем оставшиеся символы нулями
        dest[i++] = '\0';
      }
      break;
    }
    i++;
  }
  return dest;  // Возвращаем указатель на начало скопированной строки
}

// Вычисление длины начального сегмента строки 'str', состоящего из символов,
// не входящих в строку 'sym'
s21_size_t s21_strcspn(const char *str, const char *sym) {
  s21_size_t len = 0;  // Инициализируем длину сегмента
  int flag = 0;  // Инициализируем флаг нахождения символа

  while (str[len] != '\0' && !flag) {
    // Цикл до конца строки или нахождения символа из 'sym'
    if (s21_strchr(sym, str[len])) {  // Проверяем на вхождение символа
      flag = 1;
    } else {
      len++;
    }
  }
  return len;
}

// Возвращение текстового описания ошибки по ее коду
char *s21_strerror(int errnum) {
  static char error_message[STRERR_MAX] = {0};
  // Инициализируем буфер для сообщения об ошибке
  ARRAY;
  if (errnum >= 0 && errnum < ERR_MAX) {  // Проверяем код ошибки
    s21_strncpy(error_message, errlist[errnum], STRERR_MAX);
    // Копируем описание ошибки в буфер error_message
  } else {
    // Обработка некорректного кода ошибки
#ifdef __APPLE__
    s21_sprintf(error_message, "Unknown error: %d", errnum);
#elif __linux__
    s21_sprintf(error_message, "Unknown error %d", errnum);
#endif
  }
  return error_message;  // Возвращаем указатель на буфер
}

// Вычисление длины строки
s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

// Поиск первого вхождения любого символа из 'str2' в строке 'str1'
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  // Цикл до конца строки 'str1' или нахождения символа из 'str2'
  while (*str1 != '\0' && res == s21_NULL) {
    if (s21_strchr(str2, *str1) != s21_NULL) {  // Проверка на вхождение символа
      res = (char *)str1;  // Сохраняем указатель
    }
    str1++;
  }
  return res;  // Возвращаем указатель или NULL
}

// Поиск последнего вхождения символа 'c' в строке 'str'
char *s21_strrchr(const char *str, int c) {
  char *last_symbol = s21_NULL;
  const char *str_end = str + s21_strlen(str);  // Находим конец строки

  while (str <= str_end) {  // Цикл до конца строки
    if (*str == c) {  // Проверяем на совпадение символа
      last_symbol = (char *)str;  // Обновляем указатель
    }
    str++;
  }
  return last_symbol;
}

// Поиск первого вхождения подстроки 'needle' в строке 'haystack'
char *s21_strstr(char *haystack, char *needle) {
  char *res = s21_NULL;
  // Проверяем, пустая ли подстрока 'needle'
  if (needle[0] == '\0') {
    // Присваеваем указатель на первый символ 'haystack' к 'res'
    res = haystack;
  }

  // Цикл по строке 'haystack' до ее конца или нахождения подстроки
  while (*haystack != '\0' && res == s21_NULL) {
    // Проверяем первый символ подстроки
    if (*haystack == *needle) {
      char *haystack_ptr = haystack;  // Запоминаем текущую позицию
      char *needle_ptr = needle;  // Запоминаем начало подстроки
      int flag = 1;

      // Сравниваем символы подстроки с haystack
      while (*needle_ptr != '\0' && flag) {
        if (*haystack_ptr != *needle_ptr) {
          // Символы не совпадают
          flag = 0;
        }
        haystack_ptr++;
        needle_ptr++;
      }

      if (flag) {
        res = haystack;
        // Сохраняем указатель
      }
    }
    haystack++;
  }
  return res;
}

// Разбиение строки 'str' на лексемы, используя разделители 'delim'
char *s21_strtok(char *str, const char *delim) {
  static char *current = s21_NULL;
  // Статическая переменная для текущей позиции

  // Если 'str' не NULL, значит это первый вызов для строки
  if (str != s21_NULL) {
    current = str;  // Устанавливаем current в начало строки
  }

  char *lexeme_start = s21_NULL;  // Инициализируем указатель на лексему

  // Если current не NULL, значит есть неразобранная строка
  if (current != s21_NULL) {  // Пропускаем разделители в начале
    while (*current != '\0' && s21_strchr(delim, *current) != s21_NULL) {
      current++;
    }
    lexeme_start = current;  // Запоминаем начало лексемы

    // Ищем конец лексемы
    while (*current != '\0' && s21_strchr(delim, *current) == s21_NULL) {
      current++;
    }
    // Если не конец строки, заменяем разделитель на '\0'
    if (*current != '\0') {
      *current++ = '\0';
    } else {
      // Если конец строки, устанавливаем current в NULL
      current = s21_NULL;
    }
  }
  return lexeme_start;  // Возвращаем указатель на лексему
}

// Преобразование строки в верхний регистр
void *s21_to_upper(const char *str) {
  char *res_str = s21_NULL;
  // Инициализируем указатель на результат
  if (str != s21_NULL) {
    s21_size_t str_len = s21_strlen(str);
    // Вычисляем длину исходной строки
    res_str = (char *)malloc((str_len + 1) * sizeof(char));
    // Выделяем память

    // Если память выделена
    if (res_str != s21_NULL) {
      s21_size_t i = 0;
      while (i <= str_len) {
        // Цикл по символам строки Если символ - строчная буква
        if (str[i] >= 'a' && str[i] <= 'z') {
          res_str[i] = str[i] - ('a' - 'A');
          // Преобразуем в верхний регистр
        } else {
          res_str[i] = str[i];
          // Иначе копируем без изменений
        }
        i++;
      }
    }
  }
  return res_str;  // Возвращаем указатель на результат
}

// Преобразование строки в нижний регистр
void *s21_to_lower(const char *str) {
  char *res_str = s21_NULL;
  // Инициализируем указатель на результат
  if (str != s21_NULL) {
    s21_size_t str_len = s21_strlen(str);
    // Вычисляем длину строки
    res_str = (char *)malloc((str_len + 1) * sizeof(char));
    // Выделяем память

    if (res_str != s21_NULL) {
      // Проверяем выделение памяти
      s21_size_t i = 0;
      while (i <= str_len) {
        // Цикл по символам строки
        if (str[i] >= 'A' && str[i] <= 'Z') {
          // Если символ - заглавная буква
          res_str[i] = str[i] + ('a' - 'A');
          // Преобразуем в нижний регистр
        } else {
          res_str[i] = str[i];
          // Иначе копируем без изменений
        }
        i++;
      }
    }
  }
  return res_str;  // Возвращаем указатель на результат
}

// Вставка подстроки 'str' в строку 'src' по индексу 'start_index'
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res_str = s21_NULL;  // Инициализируем указатель на результат

  if (src != s21_NULL && str != s21_NULL) {
    s21_size_t src_len = s21_strlen(src);
    // Вычисляем длину строки 'src'
    s21_size_t str_len = s21_strlen(str);
    // Вычисляем длину вставляемой строки 'str'

    // Проверяем индекс вставки
    if (start_index <= src_len) {
      // Выделяем память под результат
      res_str = (char *)malloc((src_len + str_len + 1) * sizeof(char));
      if (res_str != s21_NULL) {
        // Проверяем, выделилась ли память успешно
        s21_size_t i = 0;
        // Инициализируем счетчик для результатирующей строки
        s21_size_t j = 0;
        // Инициализируем счетчик для вставляемой строки

        while (i < src_len + str_len) {
          // Цикл по результирующей строке
          if (i < start_index || j >= str_len) {
            // Копируем символы 'src' до или после вставки
            res_str[i] = src[i - j];
            i++;
          } else {
            // Вставка символов из 'str'
            res_str[i] = str[j];
            i++;
            j++;
          }
        }
        res_str[src_len + str_len] = '\0';
        // Добавляем нуль-терминатор в конец строки
      }
    }
  }
  return res_str;  // Возвращаем указатель на результат
}

// Удаление начальных и конечных пробельных символов из строки 'src',
// указанных в строке 'trim_chars'
void *s21_trim(const char *src, const char *trim_chars) {
  char *res_str = s21_NULL;
  // Инициализация указателя на обрезанную строку значением NULL
  if (src != s21_NULL && trim_chars != s21_NULL) {
    const char *start_str = src;
    // Указатель на начало строки
    const char *end_str = src + s21_strlen(src) - 1;
    // Указатель на конец строки

    while (*start_str != '\0' &&
           s21_strchr(trim_chars, *start_str) != s21_NULL) {
      // Пропуск начальных пробельных символов
      start_str++;
    }

    while (end_str >= start_str &&
           s21_strchr(trim_chars, *end_str) != s21_NULL) {
      // Пропуск конечных пробельных символов
      end_str--;
    }

    s21_size_t result_len = end_str - start_str + 1;
    // Вычисление длины обрезанной строки
    res_str = (char *)malloc((result_len + 1) * sizeof(char));
    // Выделение памяти под обрезанную строку

    if (res_str != s21_NULL) {
      // Проверка на успешное выделение памяти
      s21_size_t i = 0;

      while (i < result_len) {
        // Цикл копирования символов обрезанной строки
        res_str[i] = start_str[i];
        // Копирование символа
        i++;
      }

      res_str[result_len] = '\0';
      // Добавление нуль-терминатора в конец строки
    }
  }
  return res_str;
  // Возвращение указателя на обрезанную строку или NULL,
  // если произошла ошибка выделения памяти или указатели на
  // строки NULL
}