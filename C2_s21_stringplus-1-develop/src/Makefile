FLAGS = -Wall -Werror -Wextra -pedantic -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
FILES = tests.c s21_string.c s21_sprintf.c s21_sscanf.c common.c
OS := $(shell uname -s)
ISWSL := $(shell uname -r | grep WSL -o)
LIBCHECK := $(shell pkg-config --libs check)

ifeq ($(ISWSL), WSL)
	HTML_OPEN = @echo HTML report is in $(shell pwd)/report/index.html
else ifeq ($(OS), Linux)
	HTML_OPEN = @xdg-open ./report/index.html
else
	HTML_OPEN = @open ./report/index.html
endif

all: test

check:
ifeq ("", "$(shell which lcov)")
	$(error "Please install lcov")
endif
ifeq ("", "$(shell which pkg-config)")
	$(error "Please install pkg-config")
else ifeq ("", "$(LIBCHECK)")
	$(error "Please install check")	
endif
ifneq ($(ISWSL), WSL)
ifeq ($(OS), Linux)
ifeq ("", "$(shell which xdg-open)")
	$(error "Please install xdg-open (xdg-utils)")
endif
endif
endif
test: check s21_string.a
	gcc $(FLAGS) tests.c s21_string.a -o tests.out $(LIBCHECK)
	./tests.out
	clang-format -n --style=google $(FILES)
gcov_report: check s21_string.a
	@rm -rf report
	gcc $(FLAGS) $(GCOV_FLAGS) $(FILES) -o gcov.out $(LIBCHECK)
	./gcov.out
	clang-format -n --style=google $(FILES)
	lcov -t "s21_string" -o s21_string.info -c -d . -q --rc branch_coverage=1
	genhtml -o report s21_string.info -q --rc branch_coverage=1
	@rm -f s21_string.info *.gcda *.gcno gcov.out
	$(HTML_OPEN)
s21_string.a:
	gcc $(FLAGS) -c -o s21_string.o -c s21_string.c
	gcc $(FLAGS) -c -o s21_sprintf.o s21_sprintf.c
	gcc $(FLAGS) -c -o s21_sscanf.o s21_sscanf.c
	gcc $(FLAGS) -c -o common.o common.c
	ar rcs s21_string.a s21_string.o s21_sprintf.o s21_sscanf.o common.o
	@rm -f s21_string.o s21_sprintf.o s21_sscanf.o common.o
clean:
	rm -f s21_string.a tests.out *.o s21_string.info *.gcda *.gcno gcov.out
	rm -rf report
rebuild: clean all

clang:
	clang-format -i -style=google *.c *.h