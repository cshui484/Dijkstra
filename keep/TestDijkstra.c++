// --------------------------------
// projects/dijkstra/TestDijkstra.c++
// Copyright (C) 2015
// CS Hui
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Dijkstra.h"

using namespace std;

// -----------
// TestDijkstra
// -----------

// ----
// read
// ----

TEST(DijkstraFixture, read) {
    string s("1 10\n");
    const pair<int, int> p = dijkstra_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(DijkstraFixture, read1) {
	int i, j, k;
    string s("1 10 100\n");
    const tuple<int, int, int> t = dijkstra_read1(s);
    tie(i, j, k) = t;
    ASSERT_EQ( 1, i);
    ASSERT_EQ(10, j);
    ASSERT_EQ(100, k);}

// ----
// eval
// ----

/*
TEST(DijkstraFixture, eval_4) {
    const int v = dijkstra_eval(3, 11);
    ASSERT_EQ(3, v);}
*/

// -----
// print
// -----

TEST(DijkstraFixture, print) {
	vector<int> v = {1, 2, 3, 4};
    ostringstream w;
    dijkstra_print(w, v);
    ASSERT_EQ("1 2 3 4 \n", w.str());}

// -----
// solve
// -----

TEST(DijkstraFixture, solve) {
    istringstream r("3 2\n2 3 4\n1 2 3\n");
    ostringstream w;
    dijkstra_solve(r, w);
    ASSERT_EQ("1 2 3 \n", w.str());}

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Dijkstra.c++ TestDijkstra.c++ -o TestDijkstra -lgtest -lgtest_main -lpthread



% valgrind TestDijkstra                                         >  TestDijkstra.out 2>&1
% gcov -b Dijkstra.c++     | grep -A 5 "File 'Dijkstra.c++'"     >> TestDijkstra.out
% gcov -b TestDijkstra.c++ | grep -A 5 "File 'TestDijkstra.c++'" >> TestDijkstra.out



% cat TestDijkstra.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestDijkstra
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Dijkstra
[ RUN      ] Dijkstra.read
[       OK ] Dijkstra.read (31 ms)
[ RUN      ] Dijkstra.eval_1
[       OK ] Dijkstra.eval_1 (5 ms)
[ RUN      ] Dijkstra.eval_2
[       OK ] Dijkstra.eval_2 (3 ms)
[ RUN      ] Dijkstra.eval_3
[       OK ] Dijkstra.eval_3 (3 ms)
[ RUN      ] Dijkstra.eval_4
[       OK ] Dijkstra.eval_4 (3 ms)
[ RUN      ] Dijkstra.print
[       OK ] Dijkstra.print (17 ms)
[ RUN      ] Dijkstra.solve
[       OK ] Dijkstra.solve (10 ms)
[----------] 7 tests from Dijkstra (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Dijkstra.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Dijkstra.c++.gcov'
File 'TestDijkstra.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestDijkstra.c++.gcov'
*/
