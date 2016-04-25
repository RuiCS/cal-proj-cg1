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

#define MIN_LAT 41.14
#define MAX_LAT 41.20
#define MIN_LON -8.56
#define MAX_LON -8.70

#define WIN_WIDTH 3000
#define WIN_HEIGHT 3000

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

	float pathWeight(const Stop& s1, const Stop &s2);
	vector<Stop> findLightestPath(string s1, string s2, float& weight);
	void findFastestPath(string s1, string s2);
	void findCheapestPath(string s1, string s2);
	void findShortestPath(string s1, string s2);
	void findLeastLineSwitchesPath(string s1, string s2);
};

bool exists_in_vector(vector<string> v, string s);
void graphView(NetworkMap nm);
int findVertexInVector(vector <Vertex<Stop>*> vertexSet, Vertex<Stop>* to_find);
void resetEdges(float(*weightFunction)(const Stop&, const Stop&), NetworkMap& nm);
float calcPrice(int numZones);

// Methods to calculate edge weight
float testWeight(const Stop& s1, const Stop& s2);
float timeWeight(const Stop& s1, const Stop& s2);
float priceWeight(const Stop& s1, const Stop& s2);
float distanceWeight(const Stop& s1, const Stop& s2);
float lineSwitchWeight(const Stop&s1, const Stop& s2);

#endif /* SRC_NETWORKMAP_H_ */
