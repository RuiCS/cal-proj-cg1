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

#define SUBWAY_VEL 50
#define SUBWAY_INSTOP 60

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
	float calcTimeBetween(const Stop &s1, const Stop &s2);
	void calcTimeBetweenStops();
	int calcNumberOfLineSwitchesBetween(const Stop &s1, const Stop &s2);
	void calcSwitchesBetweenStops();
};

bool exists_in_vector(vector<string> v, string s);
void graphView(NetworkMap nm);
int findVertexInVector(vector <Vertex<Stop>*> vertexSet, Vertex<Stop>* to_find);

#endif /* SRC_NETWORKMAP_H_ */
