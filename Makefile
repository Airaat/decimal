CC=gcc
AR=ar
ARGLAGS=rcs
CFLAGS=-Wall -Werror -Wextra -std=c11 -g
LIBFLAGS=-lm -lcheck
GCOV_FLAGS=--coverage
BIN=test

OS=$(shell uname -s)
ifeq ($(OS), Linux)
	LIBFLAGS+=-lsubunit
endif

.PHONY: all s21_decimal.a rebuild clean clang

all: s21_decimal.a

s21_decimal.a: 
	$(CC) -c $(CFLAGS) src/s21_*.c
	$(AR) $(ARGLAGS) s21_decimal.a *.o
	rm *.o

test: s21_decimal.a
	$(CC) $(CFLAGS) -o $(BIN) src/unit_tests.c s21_decimal.a $(LIBFLAGS)
	./$(BIN)


rebuild: clean all

gcov_report: s21_decimal.a
	$(CC) $(GCOV_FLAGS) $(CFLAGS) -o $(BIN) src/unit_tests.c s21_decimal.a $(LIBFLAGS)
	./$(BIN)
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	rm -rf *.g* *.info
	open ./report/index.html

leaks: s21_decimal.a
	$(CC) $(CFLAGS) -o $(BIN) src/unit_tests.c s21_decimal.a $(LIBFLAGS)
	valgrind --tool=memcheck --leak-check=yes ./$(BIN)

clean:
	rm -rf a.out *.a $(BIN) *.o report *.g* *.info

clang:
	clang-format --style=Google -n *.c *.h
	clang-format --style=Google -i *.c *.h

