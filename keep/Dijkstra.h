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


// -------------
// dijkstra_print
// -------------

/**
 * print single int
 * @param w an ostream
 * @param v the min number of button pressed
 */
void dijkstra_print (ostream& w, vector<int> &v);

// -------------
// dijkstra_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void dijkstra_solve (istream& r, ostream& w);

#endif // Dijkstra_h
