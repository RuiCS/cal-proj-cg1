/*
 *  NetworkMap.h
 */
#ifndef SRC_NETWORKMAP_H
#define SRC_NETWORKMAP_H

#include "Graph.h"
#include "Stop.h"
#include <string>
#include <fstream>
#include <string.h>
#include <sstream>

class NetworkMap {
	Graph<Stop> map;
public:
	NetworkMap();
	bool loadMap(string filepath);
};

#endif
