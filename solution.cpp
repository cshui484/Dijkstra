// --------------------------
// projects/dijkstra/Dijkstra.h
// Copyright (C) 2015
// CS Hui
// --------------------------

#ifndef Dijkstra_h
#define Dijkstra_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>

using namespace std;

// ------------
// class Node
// ------------

class Node {
	public:
		int		id;
		int 	weight		= 0;
		int 	pId			= 0;
		bool	visited		= false;
		bool	done		= false;
		
		vector < vector<int> > 	children; 

		
		Node (int nId) {
			id = nId; }

			
		void append (int cId, int w) {
			vector<int> v = { cId, w };
			children.push_back(v); }

			
		void print () {
			cout << "id = " << id << " weight = " << weight << " pId = " << pId \
			     << " visited = " << visited << " done = " << done << " children = ";
			if (children.size() == 0) {
				cout << "None"; }
			else {
				cout << "[ ";
				for (unsigned int i=0; i<children.size(); i++) {
					cout << "(";
					unsigned int j;
					for (j=0; j<children[i].size()-1; j++) {
						cout << children[i][j] << ", "; }
					cout << children[i][j] << ") "; }}
			cout << "]" << endl; }


		void printNodes(vector<Node> &nodes) {
			for (int i=0; i<(int)nodes.size(); i++) {
				nodes[i].print(); }}

			
		void clrSP (vector<Node> &nodes) {
			int numNode = (int) nodes.size();
			for (int i=1; i<numNode; i++) {
				nodes[i].weight  = 0;
				nodes[i].visited = false;
				nodes[i].done	 = false; }}

				
		void setSP (vector<Node> &nodes) {
			int 	numNeighbor = (int) children.size();
			int 	nId, wt, tpw, tnw;			
			if (done) { return; }					// skip because this node has been processed
			for (int i=0; i<numNeighbor; i++) {
				nId = children[i][0];
				wt  = children[i][1];
				if (nId != pId) {					// skip if this route has been processed
					tpw = weight + wt;
					if (! nodes[nId].visited) {		// update n if needed	
						nodes[nId].weight  = tpw;
						nodes[nId].pId	   = id;
						nodes[nId].visited = true; }
					else if (nodes[nId].weight > tpw) {
						nodes[nId].weight  = tpw;
						nodes[nId].pId	   = id;
						nodes[nId].done    = false; }
					tnw = nodes[nId].weight + wt;
					if (weight > tnw) {				// update self is needed
						weight = tnw;
						pId    = nId;
						setSP(nodes); }}}			// re-do setSP again
			done = true;
			
			// time to call setSP() recusively for all the neighbors
			
			for (int i=0; i<numNeighbor; i++) {	
				nId = children[i][0];
				nodes[nId].setSP(nodes); }}
				
				
		vector<int> getReversedSP (int dId, vector<Node> &nodes) {
			vector<int> path;
			clrSP(nodes);
			visited 		= true;			// src  node is always visited
			nodes[dId].done = true;			// dest node is always done
			setSP(nodes);
			
			// SP info is available, time to retrive it
			
			path.push_back(nodes[dId].id);
			while (nodes[dId].id != id) {
				path.push_back(nodes[dId].pId);
				nodes[dId] = nodes[nodes[dId].pId]; }				
			return path; }	
				
				
		vector<int> getSP(int dId, vector<Node> &nodes) {
			vector<int> path;
			path = getReversedSP(dId, nodes);
			reverse(path.begin(), path.end());
			return path; }
						
};

void printNodes(vector<Node> &nodes);
void printVec(vector<int> &v);
			
// ------------
// dijkstra_read
// ------------

/**
 * read two ints
 * @param s a string
 * @return a pair of ints, representing the numbers of node and branches [n, b]
 */
pair<int, int> dijkstra_read (const string& s);

// ------------
// dijkstra_read1
// ------------

/**
 * read three ints
 * @param s a string
 * @return a tuple of 3 ints, representing the 2 nodes and weight [n1, n2, w]
 */
tuple<int, int, int> dijkstra_read1 (const string& s);

// ------------
// dijkstra_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the min number of button pressed for numbers [i, j]
 */
//vector<int> dijkstra_eval (vector<Node> &nodes, vector <vector<int> > &edges);
//vector<int> dijkstra_eval (int numNode, map <int, vector<int> > &neighbor, map<pair<int, int>, int> &cost);
vector<int> dijkstra_eval (int numNode, map <int, vector<int> > &neighbor, map<int, vector<int>> &cost);
//string dijkstra_eval (int numNode, map <int, vector<int> > &neighbor, map<int, vector<int>> &cost);


// -------------
// dijkstra_print
// -------------

/**
 * print single int
 * @param w an ostream
 * @param v the min number of button pressed
 */
void dijkstra_print (ostream& w, vector<int> &v);
//void dijkstra_print (ostream& w, string &v);

// -------------
// dijkstra_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void dijkstra_solve (istream& r, ostream& w);

#endif // Dijkstra_h
// ----------------------------
// projects/dijkstra/Dijkstra.c++
// Copyright (C) 2015
// CS Hui
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <queue>
#include <functional>
#include <map>
#include <climits>



using namespace std;

// ------------
// dijkstra_read
// ------------

pair<int, int> dijkstra_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// dijkstra_read1
// ------------

tuple <int, int, int> dijkstra_read1 (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    int z;
    sin >> i >> j >> z;
    return make_tuple(i, j, z);}

// ------------
// dijkstra_eval
// ------------

vector<int> dijkstra_eval (int numNode, map <int, vector<int> > &neighbor, map<int, vector<int>> &cost) {
//string dijkstra_eval (int numNode, map <int, vector<int> > &neighbor, map<int, vector<int>> &cost) {

//	pair<int, int> p1, p2;
	priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> q;

/*
	auto comp = [vector<int>weight] (int &a, int &b) -> bool { return weight[a] < weight[b]; };
	priority_queue< int, vector<int>, decltype(comp) > q(comp);
*/

	vector<int> path;
//	string path = "";
	vector<bool> done(numNode+1, false);
	vector<int> weight(numNode+1, INT_MAX);
	map<int, int> pId;

	int tc, nId;
	int sId = numNode;
	int dId = 1;

//	while(sId != dId) {
	while(sId != 1) {
		if (done[sId] == false) {						// because priority queue may have multiple
			int cnt = (int) neighbor[sId].size();		//   entries for the same sId
			for (int i=0; i<cnt; i++) {
				nId = neighbor[sId][i];
				if (done[nId] == true) { continue; }			
				tc = weight[sId] + cost[sId][i];
				if (weight[nId] > tc) {
					weight[nId] = tc;
					q.push(make_pair(tc, nId));
//					q.push(nId);
//					neighbor[nId].erase(remove(neighbor[nId].begin(), neighbor[nId].end(), sId), neighbor[nId].end());
					pId[nId] = sId;}}
			done[sId] = true; }
		if (q.size() == 0)  {
//			break; }
			path.push_back(-1);
			return path; }
			
		sId = q.top().second;
//		sId = q.top();
		q.pop(); }

	sId = numNode;
	if (pId[dId] == 0) {
		path.push_back(-1); }
//		path = to_string(-1); }
	else {
		path.push_back(dId);
//		path += to_string(dId);
		while (dId != sId) {		
			path.push_back(pId[dId]);
//			path += " " + to_string(pId[dId]) ;
			dId = pId[dId]; }}

	return path;
}


// -------------
// printVec
// -------------

void printVec(vector<int> &v) {
	int i;
	cout << "[";
	for (i=0; i<(int)v.size()-1; i++) {
		cout << v[i] << " "; }
	cout << v[i] << "]" << endl;
}

// -------------
// printNotes
// -------------

void printNodes(vector<Node> &nodes) {
	for (int i=1; i<(int)nodes.size(); i++) {
		nodes[i].print(); }
}


// -------------
// dijkstra_print
// -------------

void dijkstra_print (ostream& w, vector<int> &v) {
//void dijkstra_print (ostream& w, string &v) {

	for (unsigned int i=0; i<v.size(); i++) {
    	w << v[i] << ' '; }
    w << endl; }

//	w << v << endl; }  
    
// -------------
// dijkstra_solve
// -------------

void dijkstra_solve (istream& r, ostream& w) {
//    string 	s;
//    bool	fLine = true;

//    pair<int, int> 			p, p1, p2;
    int						n1, n2, wt;
//    tuple <int, int, int>	t;
	map<int, vector<int> > 	neighbor, cost;
//	map<pair<int, int>, int> cost;
//	istringstream sin;
	int numNode, numEdge;

/*
	getline(r, s);
	sin.str(s);
	sin >> numNode >> numEdge;
*/

	r >> numNode >> numEdge;

//    while (getline(r, s)) {
	for (int i=0; i<numEdge; i++) {
/*
    	if (fLine) {
 			fLine = false;
        	p = dijkstra_read(s);
		}
		else {
*/
//			istringstream sin(s);

			r >> n1 >> n2 >> wt;
			neighbor[n1].push_back(n2);
/*
			p1 = make_pair(n1, n2);		
			p2 = make_pair(n2, n1);
*/

/*
			if (cost.count(p1) == 1) {
				if (cost[p1] > wt) {
					cost[p1] = wt;
					cost[p2] = wt; }}
			else {
*/
			
					neighbor[n2].push_back(n1);
/*				
					cost[p1] = wt;
					cost[p2] = wt; }}
*/
					cost[n1].push_back(wt);
					cost[n2].push_back(wt); }


									
//    vector<int> path = dijkstra_eval(p.first, neighbor, cost);
    vector<int> path = dijkstra_eval(numNode, neighbor, cost);
//    string path = dijkstra_eval(numNode, neighbor, cost);
    dijkstra_print(w, path); }
       
    
    
    
    
// ------------------------------/
// projects/dijkstra/RunDijkstra.c++
// Copyright (C) 2015
// CS Hui
// -------------------------------

// --------
// includes
// --------

#include <iostream> // cin, cout



// ----
// main
// ----

int main () {
    using namespace std;
    dijkstra_solve(cin, cout);
    return 0;}

/*
% g++ -pedantic -std=c++11 -Wall Dijkstra.c++ RunDijkstra.c++ -o RunDijkstra



% cat RunDijkstra.in
1 10
100 200
201 210
900 1000



% RunDijkstra < RunDijkstra.in > RunDijkstra.out



% cat RunDijkstra.out
1 10 1
100 200 1
201 210 1
900 1000 1



% doxygen -g
// That creates the file Doxyfile.
// Make the following edits to Doxyfile.
// EXTRACT_ALL            = YES
// EXTRACT_PRIVATE        = YES
// EXTRACT_STATIC         = YES



% doxygen Doxyfile
// That creates the directory html/.
*/
