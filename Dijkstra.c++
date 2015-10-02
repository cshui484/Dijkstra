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

#include "Dijkstra.h"

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
       
    
    
    
    
