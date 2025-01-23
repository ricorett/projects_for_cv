CC = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
CHECKFLAGS = -lgtest
GCOVFLAGS = -fprofile-arcs -ftest-coverage --coverage

TEST_ENTRY = tests.cpp
EXECUTABLE_FILE = $(basename $(TEST_ENTRY))

all: clean test

$(EXECUTABLE_FILE):
	$(CC) $(CPPFLAGS) $(TEST_ENTRY) -o $(EXECUTABLE_FILE) $(CHECKFLAGS)

test: $(EXECUTABLE_FILE)
	./$(EXECUTABLE_FILE)

clean:
	@rm -rf $(EXECUTABLE_FILE) *.gcno *.gcda report *.info

gcov_report:
	$(CC) $(CPPFLAGS) $(GCOVFLAGS) $(TEST_ENTRY) -o $(EXECUTABLE_FILE) $(CHECKFLAGS)
	./$(EXECUTABLE_FILE)
	@lcov -t "gcov_report" -o Coverage_Report.info --no-external -c -d . -q --ignore-errors mismatch,mismatch
	@genhtml -o report/ Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open report/index.html

style_check:
	clang-format -n --style=google *.h *.cpp

style_fix:
	clang-format -i --style=google *.h *.cpp

memcheck: $(EXECUTABLE_FILE)
ifeq ($(shell uname), Linux)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(EXECUTABLE_FILE)
else
	leaks -atExit -- ./main.out | grep LEAK:
endif

