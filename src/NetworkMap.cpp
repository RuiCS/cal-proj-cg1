#include "NetworkMap.h"

NetworkMap::NetworkMap() {
	map = Graph<Stop>();
}

bool NetworkMap::loadMap(string filepath) {
    string node, name, zone, slat, slon;
    float lat, lon;

	ifstream infile(filepath.c_str());
	string line;
	while (getline(infile, line)) {
        stringstream lineStream(line);
        getline(lineStream, node, ',');
        getline(lineStream, name, ',');
        getline(lineStream, zone, ',');
        getline(lineStream, slat, ',');
        getline(lineStream, slon, ',');
        lat = stof(slat);
        lon = stof(slon);

        Stop stop = Stop(name, lat, lon, node);
        map.addVertex(stop);

        //...
	}
	return true;
}
