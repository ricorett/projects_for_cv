LFLAGS=-lcheck -L. -ls21_math -lm #-lsubunit 
CFLAGS=-Wall -Werror -Wextra -pedantic -std=c11
GCOV_FLAGS=-lgcov --coverage
CC=gcc

.PHONY: clean all rebuild

all: s21_math.a

test: libs21_math.a tests.o
	$(CC) $^ $(LFLAGS) -o $@

gcov_report: s21_math.c tests.c libs21_math.a
	$(CC) $(CFLAGS) $^ $(LFLAGS) $(GCOV_FLAGS)
	./a.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report

libs21_math.a: s21_math.a
	mv s21_math.a libs21_math.a

s21_math.a: s21_math.o
	ar -rcs $@ $^

s21_math.o: s21_math.c
	$(CC) -c $(CFLAGS) $^

tests.o: tests.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o test gcov_report *.gcda *.gcno coverage.info *.a a.out

rebuild: clean all
