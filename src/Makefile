.PHONY: all install open uninstall dist test gcov clean leak div

GCC = gcc -Wall -Werror -Wextra -std=c++17 

TEST_FLAGS = -lgtest -lgtest_main -lstdc++ -lm -g 
TEST_FILES = Tests/maze_test.cc Tests/maze_solver_test.cc Tests/maze_generator_test.cc Tests/cave_test.cc Maze/models/maze.cc Maze/models/maze_solver.cc Maze/models/maze_generator.cc Maze/models/cave_model.cc
TEST = $(GCC) $(TEST_FILES) $(TEST_FLAGS) -o s21_test


GCOVFLAGS = -fprofile-arcs -ftest-coverage

OS = $(shell uname)

ifeq ($(OS), Darwin)
	TEST_LIBS = -lcheck -lgcov
	MOVE = mkdir build && mv Maze/maze.app build
	OPEN = cd build && open .
	LEAK = leaks -atExit -- ./s21_test 
	MISSMATCH = --ignore-errors mismatch
else
	TEST_LIBS = -lcheck -lsubunit -pthread -lm -lrt -lgcov
	MOVE = mkdir build && mv Maze/maze build
	OPEN = build/maze
	LEAK = valgrind --leak-check=full ./s21_test
endif

all: uninstall install

install:
	qmake6 -o Maze/Makefile Maze/maze.pro
	cd Maze/ && make 
	$(MOVE)
	cd Maze/ && make clean && rm -rf Makefile .qmake.stash
	$(OPEN)

open:
	$(OPEN)

uninstall:
	rm -rf build/

dist:
	mkdir Maze_dist/
	cp -a Maze Exemples Tests Makefile readme.txt  Maze_dist
	tar cvzf Maze.tgz Maze_dist/
	rm -rf Maze_dist/

test:
	$(TEST)
	./s21_test

gcov: 
	$(GCC) $(GCOVFLAGS) $(TEST_FILES) $(TEST_FLAGS) -o report.out
	./report.out
	lcov -t "gcov_report" -o gcov_report.info --no-external -c -d . $(MISSMATCH)
	genhtml -o report/ gcov_report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index.html



clean: 
	find . \( -name '*.o' -o -name '*.a' -o -name '*.gcno' -o -name '*.gcda' -o -name '*.info' \) -exec rm -rf {} \;
	rm -rf report report_out report.out.dSYM s21_test.dSYM s21_test maze.tgz view maze.pro.*
	cd Maze/ && make clean && rm -rf Makefile .qmake.stash maze.app

clang:
	find . -name '*.cc' -o -name '*.h' | xargs clang-format -n -style=Google

leak: 
	$(TEST)
	$(LEAK)

dvi:
	open readme.txt


