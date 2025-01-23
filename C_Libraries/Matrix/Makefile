LFLAGS=-L. -ls21_matrix  -lm  -lcheck
CFLAGS=-std=c11 -Werror -Wall -Wextra 


GCOV_FLAGS=--coverage -lgcov  -L/opt/homebrew/opt/lcov
# GCOV_FLAGS=--html --html-details -o gcov_report/index.html
CC=gcc

SOURCES = $(wildcard ./funcs/*.c)
OBJECTS = $(SOURCES:.c=.o)

%.o: %.c s21_matrix.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean all rebuild

all: s21_matrix.a test

test: libs21_matrix.a tests.o
	$(CC) $(OBJECTS) $^ $(LFLAGS) -o $@

gcov_report: $(SOURCES) libs21_matrix.a tests.c
	$(CC) $(CFLAGS) $^ -o gcov_test $(LFLAGS) --coverage
	./gcov_test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	rm -f gcov_test

s21_matrix.a: $(OBJECTS) 
	ar -rcs $@ $^

libs21_matrix.a: s21_matrix.a
	cp s21_matrix.a libs21_matrix.a


tests.o: tests.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.gcno *.o ./funcs/*.o test gcov_report *.gcda  coverage.info *.a a.out

rebuild: clean all