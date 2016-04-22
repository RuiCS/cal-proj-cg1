#include "NetworkMap.h"

// Constructors -----------------------------------------------------------------

NetworkMap::NetworkMap() {
	map = Graph<Stop>();
}

// Methods -----------------------------------------------------------------

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

        stringstream latStream(slat);
        latStream >> lat;
        stringstream lonStream(slon);
        lonStream >> lon;

        cout << "Stop(" << name << ", " << lat << ", " << lon << ", " << node << ", (!!!!)" << zone <<  ");\n";

        Stop stop = Stop(name, lat, lon, node);
        map.addVertex(stop);

        //...
	}
	return true;
}
