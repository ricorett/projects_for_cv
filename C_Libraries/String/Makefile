LFLAGS=-L/opt/homebrew/opt/check/lib -lcheck -L. -ls21_string
CFLAGS=#-Wall -Werror -Wextra -pedantic -std=c11
GCOV_FLAGS=-lgcov --coverage
CC=gcc

.PHONY: clean all rebuild

all: s21_string.a

test: libs21_string.a tests.o
	$(CC) $^ $(LFLAGS) -o $@

gcov_report: s21_string.c tests.c libs21_string.a
	$(CC) $(CFLAGS) $^ $(LFLAGS) $(GCOV_FLAGS)
	./a.out
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report

libs21_string.a: s21_string.a
	mv s21_string.a libs21_string.a

s21_string.a: s21_string.o
	ar -rcs $@ $^

s21_string.o: s21_string.c
	$(CC) -c $(CFLAGS) $^

tests.o: tests.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o test gcov_report *.gcda *.gcno coverage.info *.a a.out

rebuild: clean all
