char length_define(const char** format) {
  char length = '0';
  if (**format == 'l') {
    *format += 1;
    length = 'l';
  } else if (**format == 'L') {
    *format += 1;
    length = 'L';
  } else if (**format == 'h') {
    *format += 1;
    length = 'h';
  }
  return length;
}
