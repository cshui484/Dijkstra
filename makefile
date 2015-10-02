CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunDijkstra
	rm -f RunDijkstra.tmp
	rm -f TestDijkstra
	rm -f TestDijkstra.tmp
	rm -f solution

config:
	git config -l

scrub:
	make  clean
	rm -f  Dijkstra.log
	rm -rf dijkstra-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunDijkstra.tmp TestDijkstra.tmp

solution: solution.cpp
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) solution.cpp -o solution

RunDijkstra: Dijkstra.h Dijkstra.c++ RunDijkstra.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Dijkstra.c++ RunDijkstra.c++ -o RunDijkstra

RunDijkstra.tmp: RunDijkstra
	./RunDijkstra < RunDijkstra.in > RunDijkstra.tmp
	diff -w RunDijkstra.tmp RunDijkstra.out

TestDijkstra: Dijkstra.h Dijkstra.c++ TestDijkstra.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Dijkstra.c++ TestDijkstra.c++ -o TestDijkstra $(LDFLAGS)

TestDijkstra.tmp: TestDijkstra
	$(VALGRIND) ./TestDijkstra                                       >  TestDijkstra.tmp 2>&1
	$(GCOV) -b Dijkstra.c++     | grep -A 5 "File 'Dijkstra.c++'"     >> TestDijkstra.tmp
	$(GCOV) -b TestDijkstra.c++ | grep -A 5 "File 'TestDijkstra.c++'" >> TestDijkstra.tmp
	cat TestDijkstra.tmp
