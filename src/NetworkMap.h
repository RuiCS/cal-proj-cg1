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
};

#endif /* SRC_NETWORKMAP_H_ */
