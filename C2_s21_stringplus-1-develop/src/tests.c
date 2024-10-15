#include <check.h>
#include <string.h>

#include "s21_string.h"

START_TEST(s21_memchrTest) {
  char str1[100] = "abc aboba";
  char chr1 = 'o';
  char *res1 = memchr(str1, chr1, 9);
  char *res1_s21 = s21_memchr(str1, chr1, 9);
  ck_assert_str_eq(res1, res1_s21);
  char str2[100] = "test2null";
  char chr2 = 'p';
  char *res2 = memchr(str2, chr2, 9);
  char *res2_s21 = s21_memchr(str2, chr2, 9);
  ck_assert_int_eq(res2 == NULL, res2_s21 == NULL);
  char str3[100] = "";
  char chr3 = 'A';
  char *res3 = memchr(str3, chr3, 1);
  char *res3_s21 = s21_memchr(str3, chr3, 1);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
}
END_TEST

START_TEST(s21_memcmpTest) {
  char str1_1[100] = "aboba";
  char str1_2[100] = "boabo";
  int res1 = memcmp(str1_1, str1_2, 5);
  int res1_s21 = s21_memcmp(str1_1, str1_2, 5);
  ck_assert_int_eq(res1, res1_s21);
  char str2_1[100] = "vsemprivet";
  char str2_2[100] = "vsemprivet";
  int res2 = memcmp(str2_1, str2_2, 10);
  int res2_s21 = s21_memcmp(str2_1, str2_2, 10);
  ck_assert_int_eq(res2, res2_s21);
  char str3_1[100] = "";
  char str3_2[100] = "a";
  int res3 = memcmp(str3_1, str3_2, 10);
  int res3_s21 = s21_memcmp(str3_1, str3_2, 10);
  ck_assert_int_eq(res3, res3_s21);
}
END_TEST

START_TEST(s21_memcpyTest) {
  char str1[100] = "prikol";
  char dest1[100] = "aaa", dest1_s21[100] = "aaa";
  memcpy(dest1, str1, 6);
  s21_memcpy(dest1_s21, str1, 6);
  ck_assert_str_eq(dest1, dest1_s21);
  char str2[100] = "0";
  char dest2[100] = "ddd", dest2_s21[100] = "ddd";
  memcpy(dest2, str2, 1);
  s21_memcpy(dest2_s21, str2, 1);
  ck_assert_str_eq(dest2, dest2_s21);
  char str3[100] = "";
  char dest3[100], dest3_s21[100];
  memcpy(dest3, str3, 1);
  s21_memcpy(dest3_s21, str3, 1);
  ck_assert_int_eq(dest3 == NULL, dest3_s21 == NULL);
}
END_TEST

START_TEST(s21_memsetTest) {
  char str1[100] = "this is test1", str1_s21[100] = "this is test1";
  char chr1 = '!';
  memset(str1, chr1, 7);
  s21_memset(str1_s21, chr1, 7);
  ck_assert_str_eq(str1, str1_s21);
  char str2[100], str2_s21[100];
  char chr2 = 'a';
  memset(str2, chr2, 6);
  s21_memset(str2_s21, chr2, 6);
  ck_assert_int_eq(str2 == NULL, str2_s21 == NULL);
  char str3[100] = "TEST 3 (vsem privet)",
       str3_s21[100] = "TEST 3 (vsem privet)";
  char chr3 = 'a';
  memset(str3, chr3, 5);
  s21_memset(str3_s21, chr3, 5);
  ck_assert_str_eq(str3, str3_s21);
}
END_TEST

START_TEST(s21_strncatTest) {
  char str1_1[100] = "vse\0m", str1_1_s21[100] = "vse\0m";
  char str1_2[100] = " privet";
  strncat(str1_1, str1_2, 7);
  s21_strncat(str1_1_s21, str1_2, 7);
  ck_assert_str_eq(str1_1, str1_1_s21);
  char str2_1[100] = "test", str2_1_s21[100] = "test";
  char str2_2[100] = "";
  strncat(str2_1, str2_2, 5);
  s21_strncat(str2_1_s21, str2_2, 5);
  ck_assert_str_eq(str2_1, str2_1_s21);
  char str3_1[100] = "", str3_1_s21[100] = "";
  char str3_2[100] = "egor";
  strncat(str3_1, str3_2, 7);
  s21_strncat(str3_1_s21, str3_2, 7);
  ck_assert_str_eq(str3_1, str3_1_s21);
}
END_TEST

START_TEST(s21_strchrTest) {
  char str1[100] = "abc aboba";
  char chr1 = 'o';
  char *res1 = strchr(str1, chr1);
  char *res1_s21 = s21_strchr(str1, chr1);
  ck_assert_str_eq(res1, res1_s21);
  char str2[100] = "test2null";
  char chr2 = 'p';
  char *res2 = strchr(str2, chr2);
  char *res2_s21 = s21_strchr(str2, chr2);
  ck_assert_int_eq(res2 == NULL, res2_s21 == NULL);
  char str3[100] = "";
  char chr3 = 'A';
  char *res3 = strchr(str3, chr3);
  char *res3_s21 = s21_strchr(str3, chr3);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
}
END_TEST

START_TEST(s21_strncmpTest) {
  char str1_1[100] = "aboba\0aa";
  char str1_2[100] = "aboba";
  int res1 = strncmp(str1_1, str1_2, 8);
  int res1_s21 = s21_strncmp(str1_1, str1_2, 8);
  ck_assert_int_eq(res1, res1_s21);
  char str2_1[100] = "vsemprivet";
  char str2_2[100] = "vsemprive";
  int res2 = strncmp(str2_1, str2_2, 8);
  int res2_s21 = s21_strncmp(str2_1, str2_2, 8);
  ck_assert_int_eq(res2, res2_s21);
  char str3_1[100] = "a";
  char str3_2[100] = "b";
  int res3 = strncmp(str3_1, str3_2, 10);
  int res3_s21 = s21_strncmp(str3_1, str3_2, 10);
  ck_assert_int_eq(res3, res3_s21);
  char str4_1[100] = "\0";
  char str4_2[100] = "hello!";
  int res4 = strncmp(str4_1, str4_2, 10);
  int res5_s21 = s21_strncmp(str4_1, str4_2, 10);
  ck_assert_int_eq(res4, res5_s21);
  char str5_1[] = "abc\0";
  char str5_2[] = "abcd\0";
  int res6 = s21_strncmp(str5_1, str5_2, 4);
  int res7_s21 = strncmp(str5_1, str5_2, 4);
  ck_assert_int_eq(res6, res7_s21);
}
END_TEST

START_TEST(s21_strncpyTest) {
  char str1[100] = "priko\0t";
  char dest1[100] = "aaa", dest1_s21[100] = "aaa";
  strncpy(dest1, str1, 7);
  s21_strncpy(dest1_s21, str1, 7);
  ck_assert_str_eq(dest1, dest1_s21);
  char str2[100] = "0";
  char dest2[100] = "ddd", dest2_s21[100] = "ddd";
  strncpy(dest2, str2, 1);
  s21_strncpy(dest2_s21, str2, 1);
  ck_assert_str_eq(dest2, dest2_s21);
  char str3[100] = "";
  char dest3[100], dest3_s21[100];
  strncpy(dest3, str3, 1);
  s21_strncpy(dest3_s21, str3, 1);
  ck_assert_str_eq(dest3, dest3_s21);
}
END_TEST

START_TEST(s21_strcspnTest) {
  char str1_1[100] = "abobprivet";
  char str1_2[100] = "io";
  int res1 = strcspn(str1_1, str1_2);
  int res1_s21 = s21_strcspn(str1_1, str1_2);
  ck_assert_int_eq(res1, res1_s21);
  char str2_1[100] = "abc";
  char str2_2[100] = "privet";
  int res2 = strcspn(str2_1, str2_2);
  int res2_s21 = s21_strcspn(str2_1, str2_2);
  ck_assert_int_eq(res2, res2_s21);
  char str3_1[100] = "priva";
  char str3_2[100] = "";
  int res3 = strcspn(str3_1, str3_2);
  int res3_s21 = s21_strcspn(str3_1, str3_2);
  ck_assert_int_eq(res3, res3_s21);
}
END_TEST

START_TEST(s21_strerrorTest) {
#ifdef __APPLE__
  int tests = 108;
#elif __linux__
  int tests = 134;
#endif
  for (int i = 0; i < tests; i++) {
    char *str1 = strerror(tests);
    char *str2 = s21_strerror(tests);
    ck_assert_str_eq(str1, str2);
  }
}
END_TEST

START_TEST(s21_strlenTest) {
  char str1[100] = "bigstring";
  int res1 = strlen(str1);
  int res1_s21 = s21_strlen(str1);
  ck_assert_int_eq(res1, res1_s21);
  char str2[100] = "afjd\0dkflkf";
  int res2 = strlen(str2);
  int res2_s21 = s21_strlen(str2);
  ck_assert_int_eq(res2, res2_s21);
  char str3[100] = "";
  int res3 = strlen(str3);
  int res3_s21 = s21_strlen(str3);
  ck_assert_int_eq(res3, res3_s21);
}
END_TEST

START_TEST(s21_strpbrkTest) {
  char str1_1[100] = "vsem privet";
  char str1_2[100] = "dosvidanya";
  char *res1 = strpbrk(str1_1, str1_2);
  char *res1_s21 = strpbrk(str1_1, str1_2);
  ck_assert_str_eq(res1, res1_s21);
  char str2_1[100] = "no matches";
  char str2_2[100] = "k;\0";
  char *res2 = strpbrk(str2_1, str2_2);
  char *res2_s21 = s21_strpbrk(str2_1, str2_2);
  ck_assert_ptr_eq(res2, res2_s21);
  char str3_1[100] = "";
  char str3_2[100] = "\0";
  char *res3 = strpbrk(str3_1, str3_2);
  char *res3_s21 = s21_strpbrk(str3_1, str3_2);
  ck_assert_ptr_eq(res3, res3_s21);
}
END_TEST

START_TEST(s21_strrchrTest) {
  char str1[100] = "aboba";
  char chr1 = 'b';
  char *res1 = strrchr(str1, chr1);
  char *res1_s21 = s21_strrchr(str1, chr1);
  ck_assert_str_eq(res1, res1_s21);
  char str2[100] = "priva";
  char chr2 = 'b';
  char *res2 = strrchr(str2, chr2);
  char *res2_s21 = s21_strrchr(str2, chr2);
  ck_assert_int_eq(res2 == NULL, res2_s21 == NULL);
  char str3[100] = "";
  char chr3 = 'b';
  char *res3 = strrchr(str3, chr3);
  char *res3_s21 = s21_strrchr(str3, chr3);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
}
END_TEST

START_TEST(s21_strstrTest) {
  char str1_1[100] = "string to search";
  char str1_2[100] = "o ";
  char *res1 = strstr(str1_1, str1_2);
  char *res1_s21 = s21_strstr(str1_1, str1_2);
  ck_assert_str_eq(res1, res1_s21);
  char str2_1[100] = "abo\0bus";
  char str2_2[100] = "bus";
  char *res2 = strstr(str2_1, str2_2);
  char *res2_s21 = s21_strstr(str2_1, str2_2);
  ck_assert_int_eq(res2 == NULL, res2_s21 == NULL);
  char str3_1[100] = "";
  char str3_2[100] = "boo";
  char *res3 = strstr(str3_1, str3_2);
  char *res3_s21 = s21_strstr(str3_1, str3_2);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
}
END_TEST

START_TEST(s21_strtokTest) {
  char str1_1[100] = "big - black - cat";
  char str1_2[100] = "-";
  char *res1 = strtok(str1_1, str1_2);
  char *res1_s21 = s21_strtok(str1_1, str1_2);
  ck_assert_str_eq(res1, res1_s21);
  char str2_1[100] = "vadim";
  char str2_2[100] = "-";
  char *res2 = strtok(str2_1, str2_2);
  char *res2_s21 = s21_strtok(str2_1, str2_2);
  ck_assert_int_eq(res2 == NULL, res2_s21 == NULL);
  char *str3_1 = NULL;
  char str3_2[100] = "-";
  char *res3 = strtok(str3_1, str3_2);
  char *res3_s21 = s21_strtok(str3_1, str3_2);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
}
END_TEST

START_TEST(s21_to_upperTest) {
  char str1[100] = "sMall text";
  char *res1 = "SMALL TEXT";
  char *res1_s21 = s21_to_upper(str1);
  ck_assert_str_eq(res1, res1_s21);
  char str2[100] = "REALLYSMALLTEXT";
  char *res2 = "REALLYSMALLTEXT";
  char *res2_s21 = s21_to_upper(str2);
  ck_assert_str_eq(res2, res2_s21);
  char *str3 = NULL;
  char *res3 = NULL;
  char *res3_s21 = s21_to_upper(str3);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
  free(res1_s21);
  free(res2_s21);
  free(res3_s21);
}
END_TEST

START_TEST(s21_to_lowerTest) {
  char str1[100] = "BEEg text";
  char *res1 = "beeg text";
  char *res1_s21 = s21_to_lower(str1);
  ck_assert_str_eq(res1, res1_s21);
  char str2[100] = "reallybeegtext";
  char *res2 = "reallybeegtext";
  char *res2_s21 = s21_to_lower(str2);
  ck_assert_str_eq(res2, res2_s21);
  char *str3 = NULL;
  char *res3 = NULL;
  char *res3_s21 = s21_to_lower(str3);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
  free(res1_s21);
  free(res2_s21);
  free(res3_s21);
}
END_TEST

START_TEST(s21_insertTest) {
  char str1_1[100] = "yes i like , it's very nice";
  char str1_2[100] = "milk";
  char *res1 = "yes i like milk, it's very nice";
  char *res1_s21 = s21_insert(str1_1, str1_2, 11);
  ck_assert_str_eq(res1, res1_s21);
  char str2_1[100] = "cta is beeg";
  char str2_2[100] = "!!!";
  char *res2 = NULL;
  char *res2_s21 = s21_insert(str2_1, str2_2, 13);
  ck_assert_int_eq(res2 == NULL, res2_s21 == NULL);
  char *str3_1 = NULL;
  char *str3_2 = "a";
  char *res3 = NULL;
  char *res3_s21 = s21_insert(str3_1, str3_2, 1);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
  free(res1_s21);
  free(res2_s21);
  free(res3_s21);
}
END_TEST

START_TEST(s21_trimTest) {
  char str1_1[100] = "mmyes i like milk, it's very nicemmmm";
  char str1_2[100] = "m";
  char *res1 = "yes i like milk, it's very nice";
  char *res1_s21 = s21_trim(str1_1, str1_2);
  ck_assert_str_eq(res1, res1_s21);
  char str2_1[100] = "cta is beeg";
  char str2_2[100] = "!!!";
  char *res2 = "cta is beeg";
  char *res2_s21 = s21_trim(str2_1, str2_2);
  ck_assert_str_eq(res2, res2_s21);
  char *str3_1 = NULL;
  char *str3_2 = "a";
  char *res3 = NULL;
  char *res3_s21 = s21_trim(str3_1, str3_2);
  ck_assert_int_eq(res3 == NULL, res3_s21 == NULL);
  free(res1_s21);
  free(res2_s21);
  free(res3_s21);
}
END_TEST

START_TEST(s21_sscanfTest) {
  char *str = "7856 123 +1234567890987654321 2121212121212 123";
  int d1 = 0, d2 = 0, n1 = 0, n2 = 0, count1 = 0, count2 = 0;
  long int ld1 = 0, ld2 = 0;
  short int hd1 = 0, hd2 = 0;
  count1 = s21_sscanf(str, "%*d %d %ld %hd%n", &d1, &ld1, &hd1, &n1);
  count2 = sscanf(str, "%*d %d %ld %hd%n", &d2, &ld2, &hd2, &n2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(ld1, ld2);
  ck_assert_int_eq(hd1, hd2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(count1, count2);

  char *str_i = "123 0x65a8bd666 0407461";
  int i1 = 0, i2 = 0;
  long int li1 = 0, li2 = 0;
  short int hi1 = 0, hi2 = 0;
  s21_sscanf(str_i, "%i %li %hi", &i1, &li1, &hi1);
  sscanf(str_i, "%i %li %hi", &i2, &li2, &hi2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(li1, li2);
  ck_assert_int_eq(hi1, hi2);

  char *ustr = "-9 123456789098765432 6578613 8084";
  unsigned int u1 = 0, u2 = 0;
  long unsigned int lu1 = 0, lu2 = 0;
  short unsigned int hu1 = 0, hu2 = 0;
  count1 = s21_sscanf(ustr, "%u %lu %hu %*u", &u1, &lu1, &hu1);
  count2 = sscanf(ustr, "%u %lu %hu %*u", &u2, &lu2, &hu2);
  ck_assert_uint_eq(u1, u2);
  ck_assert_uint_eq(lu1, lu2);
  ck_assert_uint_eq(hu1, hu2);
  ck_assert_uint_eq(count1, count2);

  unsigned int o1 = 0, o2 = 0;
  long unsigned int lo1 = 0, lo2 = 0;
  short unsigned int ho1 = 0, ho2 = 0;
  count1 = s21_sscanf(ustr, "%o %lo %ho", &o1, &lo1, &ho1);
  count2 = sscanf(ustr, "%o %lo %ho", &o2, &lo2, &ho2);
  ck_assert_uint_eq(o1, o2);
  ck_assert_uint_eq(lo1, lo2);
  ck_assert_uint_eq(ho1, ho2);
  ck_assert_uint_eq(count1, count2);

  char *str_x = "privet -123abc123 1234567890abcdef0000 abc12345 aaa";
  unsigned int x1 = 0, x2 = 0;
  long unsigned int lx1 = 0, lx2 = 0;
  short unsigned int hx1 = 0, hx2 = 0;
  count1 = s21_sscanf(str_x, "%*s %x %lx %hx %*x", &x1, &lx1, &hx1);
  count2 = sscanf(str_x, "%*s %x %lx %hx %*x", &x2, &lx2, &hx2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(lx1, lx2);
  ck_assert_int_eq(hx1, hx2);
  ck_assert_int_eq(count1, count2);

  char *str2 = "! assadaker";
  char c1, c2;
  char cc1[10] = "qq";
  char cc2[10] = "qq";

  s21_sscanf(str2, "%c %s", &c1, cc1);
  sscanf(str2, "%c %s", &c2, cc2);
  ck_assert_int_eq(c1, c2);
  ck_assert_str_eq(cc1, cc2);
  s21_sscanf(str2, "%*c %3s", cc1);
  sscanf(str2, "%*c %3s", cc2);
  ck_assert_str_eq(cc1, cc2);

  char *str3 = "3.14 123456.123456 12345678987654321.1234567890987654321 300";
  char *str4 = "12e7 12e-7 12e+7";
  char *str5 = "1.5e+2 3.14";
  float fl1 = 0, fl2 = 0;
  double db1 = 0, db2 = 0;
  long double ldb1 = 0, ldb2 = 0;

  s21_sscanf(str3, "%f %lf %Lf %*f", &fl1, &db1, &ldb1);
  sscanf(str3, "%f %lf %Lf %*f", &fl2, &db2, &ldb2);
  // printf("\nld1: %Lf, ld2: %Lf\n", ldb1, ldb2);
  ck_assert_float_eq(fl1, fl2);
  ck_assert_double_eq(db1, db2);
  ck_assert_ldouble_eq(ldb1, ldb2);
  s21_sscanf(str4, "%e %lE %Le", &fl1, &db1, &ldb1);
  sscanf(str4, "%e %lE %Le", &fl2, &db2, &ldb2);
  ck_assert_float_eq(fl1, fl2);
  ck_assert_double_eq(db1, db2);
  ck_assert_ldouble_eq(ldb1, ldb2);

  s21_sscanf(str5, "%g %lg", &fl1, &db1);
  sscanf(str5, "%g %lg", &fl2, &db2);

  char *str_p = "aaa 1a2b3c\n123456789abcdef";
  void *ptr1 = "a";
  void *ptr2 = "a";
  void *ptr3 = "a";
  void *ptr4 = "a";

  s21_sscanf(str_p, "%*p %p %p", &ptr1, &ptr3);
  sscanf(str_p, "%*p %p %p", &ptr2, &ptr4);
  ck_assert_ptr_eq(ptr1, ptr2);
  ck_assert_ptr_eq(ptr1, ptr2);
}
END_TEST

START_TEST(s21_sprintfTest) {
  char buffer[100];
  char buffer2[100];
  double f = -1234567890123456789.1234567890;
  s21_sprintf(buffer, "%le", f);
  sprintf(buffer2, "%le", f);
  ck_assert_str_eq(buffer, buffer2);
  char buffer3[100];
  char buffer4[100];
  char c = 4;
  int d = 12345678;
  char *str = "eufemiabbbbb";
  float fl = 3.14, f2 = -123.456789;
  unsigned int u = -837758;
  int d2 = 45;
  int d3 = 76;
  s21_sprintf(buffer3, "Lalala zzzz%c %10s %*d %-20u %f %020f %ho %x", c, str,
              12, d, u, fl, f2, d2, d3);
  sprintf(buffer4, "Lalala zzzz%c %10s %*d %-20u %f %020f %ho %x", c, str, 12,
          d, u, fl, f2, d2, d3);
  ck_assert_str_eq(buffer3, buffer4);
  char buffer5[300];
  char buffer6[300];
  s21_sprintf(buffer5, "% d", d);
  sprintf(buffer6, "% d", d);
  ck_assert_str_eq(buffer5, buffer6);
  char buffer7[300];
  char buffer8[300];
  s21_sprintf(buffer7, "%-10o %#10x", d, d2);
  sprintf(buffer8, "%-10o %#10x", d, d2);
  ck_assert_str_eq(buffer7, buffer8);
  char buffer15[100];
  char buffer16[100];
  short int d7 = -12345;
  s21_sprintf(buffer15, "%0hd", d7);
  sprintf(buffer16, "%0hd", d7);
  ck_assert_str_eq(buffer15, buffer16);
  char buffer17[100];
  char buffer18[100];
  long int d8 = 0;
  s21_sprintf(buffer17, "%ld", d8);
  sprintf(buffer18, "%ld", d8);
  ck_assert_str_eq(buffer17, buffer18);
  char buffer19[100];
  char buffer20[100];
  long double f3 = 1234567.1234567890;
  s21_sprintf(buffer19, "%.*Lf", 13, f3);
  sprintf(buffer20, "%.*Lf", 13, f3);
  ck_assert_str_eq(buffer19, buffer20);
  char buffer21[100];
  char buffer22[100];
  s21_sprintf(buffer21, "%.2f", fl);
  sprintf(buffer22, "%.2f", fl);
  ck_assert_str_eq(buffer21, buffer22);
  char buffer23[100];
  char buffer24[100];
  s21_sprintf(buffer23, "%10d", d);
  sprintf(buffer24, "%10d", d);
  ck_assert_str_eq(buffer23, buffer24);
  char buffer9[100];
  char buffer10[100];
  s21_sprintf(buffer9, "%+d", d);
  sprintf(buffer10, "%+d", d);
  ck_assert_str_eq(buffer9, buffer10);
  char buffer11[100];
  char buffer12[100];
  s21_sprintf(buffer11, "%05d", d);
  sprintf(buffer12, "%05d", d);
  ck_assert_str_eq(buffer11, buffer12);
  char buffer13[100];
  char buffer14[100];
  s21_sprintf(buffer13, "%#X", d);
  sprintf(buffer14, "%#X", d);
  ck_assert_str_eq(buffer13, buffer14);
  char buffer25[100];
  char buffer26[100];
  int d9 = 1;
  int d10 = 1;
  char *ptr = "aaa";
  sprintf(buffer25, "%p%n", ptr, &d9);
  s21_sprintf(buffer26, "%p%n", ptr, &d10);
  ck_assert_str_eq(buffer25, buffer26);
  ck_assert_int_eq(d9, d10);
  char buffer27[100];
  char buffer28[100];
  double abc = 0.99999999;
  sprintf(buffer27, "%.2lf", abc);
  s21_sprintf(buffer28, "%.2lf", abc);
  ck_assert_str_eq(buffer27, buffer28);
  // printf("1: %s 2: %s", buffer27, buffer28);
  char buffer29[100];
  char buffer30[100];
  double abcabc = 123.12;
  sprintf(buffer29, "%#.7lg", abcabc);
  s21_sprintf(buffer30, "%#.7lg", abcabc);
  ck_assert_str_eq(buffer29, buffer30);
  char buffer31[100];
  char buffer32[100];
  sprintf(buffer31, "%.2lG", abcabc);
  s21_sprintf(buffer32, "%.2lG", abcabc);
  ck_assert_str_eq(buffer31, buffer32);
  float e = -0.000123;
  char buffer33[100];
  char buffer34[100];
  sprintf(buffer33, "%#e", e);
  s21_sprintf(buffer34, "%#e", e);
  ck_assert_str_eq(buffer33, buffer34);
}
END_TEST

int main() {
  Suite *Suite1 = suite_create("s21_stringPlus");
  TCase *TestCase1 = tcase_create("s21_string");
  SRunner *SuiteRun = srunner_create(Suite1);
  suite_add_tcase(Suite1, TestCase1);
  tcase_add_test(TestCase1, s21_memchrTest);
  tcase_add_test(TestCase1, s21_memcmpTest);
  tcase_add_test(TestCase1, s21_memcpyTest);
  tcase_add_test(TestCase1, s21_memsetTest);
  tcase_add_test(TestCase1, s21_strncatTest);
  tcase_add_test(TestCase1, s21_strchrTest);
  tcase_add_test(TestCase1, s21_strncmpTest);
  tcase_add_test(TestCase1, s21_strncpyTest);
  tcase_add_test(TestCase1, s21_strcspnTest);
  tcase_add_test(TestCase1, s21_strerrorTest);
  tcase_add_test(TestCase1, s21_strlenTest);
  tcase_add_test(TestCase1, s21_strpbrkTest);
  tcase_add_test(TestCase1, s21_strrchrTest);
  tcase_add_test(TestCase1, s21_strstrTest);
  tcase_add_test(TestCase1, s21_strtokTest);
  tcase_add_test(TestCase1, s21_to_upperTest);
  tcase_add_test(TestCase1, s21_to_lowerTest);
  tcase_add_test(TestCase1, s21_insertTest);
  tcase_add_test(TestCase1, s21_trimTest);
  tcase_add_test(TestCase1, s21_sscanfTest);
  tcase_add_test(TestCase1, s21_sprintfTest);
  srunner_run_all(SuiteRun, CK_NORMAL);
  int fails = srunner_ntests_failed(SuiteRun);
  srunner_free(SuiteRun);
  return fails;
}