/*
 *  NetworkMap.h
 */
#ifndef SRC_NETWORKMAP_H_
#define SRC_NETWORKMAP_H_

#include "Graph.h"
#include "Stop.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class NetworkMap {

	Graph<Stop> map;

public:
	//Constructors
	NetworkMap();

	//Getters
	Graph<Stop> getMap() const;

	//Setters
	void setMap(Graph<Stop> m);

	//Methods
	bool loadMap(string filepath);
	void setConnections();
	void displayMap();
};

bool exists_in_vector(vector<string> v, string s);
void graphView();
int findVertexInVector(vector <Vertex<Stop>*> vertexSet, Vertex<Stop>* to_find);

#endif /* SRC_NETWORKMAP_H_ */
