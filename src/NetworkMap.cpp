#include "NetworkMap.h"
#include <algorithm>
#include <stdlib.h>
#include <string.h>

// Constructors -----------------------------------------------------------------

NetworkMap::NetworkMap() {
	map = Graph<Stop>();
}

// Getters ----------------------------------------------------------------------

Graph<Stop> NetworkMap::getMap() const{
	return map;
}

// Setters ---------------------------------------------------------------------

void NetworkMap::setMap(Graph<Stop> m){
	map = m;
}

// Methods -----------------------------------------------------------------

bool NetworkMap::loadMap(string filepath) {
    string node, name, zone, slat, slon, time;
    float lat, lon;

	ifstream infile(filepath.c_str());
	string line;
	while (getline(infile, line)) {
        stringstream lineStream(line);
        getline(lineStream, node, ',');
        getline(lineStream, name, ',');
        getline(lineStream, zone, ',');
        getline(lineStream, time, ',');
        getline(lineStream, slat, ',');
        getline(lineStream, slon, ',');

        stringstream latStream(slat);
        latStream >> lat;
        stringstream lonStream(slon);
        lonStream >> lon;

        cout << "Stop(" << name << ", " << lat << ", " << lon << ", " << node << ", " << zone << ", " << time << ");\n";

        int intTime = atoi(time.c_str());

        Stop stop = Stop(name, lat, lon, intTime, node, zone);
        map.addVertex(stop);

        //...
	}
	return true;
}

void NetworkMap::setConnections(){

	// pressupondo que as paragens estao por ordem no ficheiro...
	for (unsigned int i = 0; i < map.getVertexSet().size() - 1; i++){

		string stop_name1, stop_name2;
		stop_name1 = map.getVertexSet()[i]->getInfo().getName();
		stop_name2 = map.getVertexSet()[i + 1]->getInfo().getName();

		stringstream st1(stop_name1);
		stringstream st2(stop_name2);
		string trash, line1, line2;

		// nome - linha
		getline(st1, trash, '-');
		getline(st1, line1);
		getline(st2, trash, '-');
		getline(st2, line2);

		if (line1 == line2){
			// PESO ?????????????????????????
			map.addEdge(map.getVertexSet()[i]->getInfo(), map.getVertexSet()[i + 1]->getInfo(), map.getVertexSet()[i + 1]->getInfo().getWaitTime());
			map.addEdge(map.getVertexSet()[i + 1]->getInfo(), map.getVertexSet()[i]->getInfo(), map.getVertexSet()[i + 1]->getInfo().getWaitTime());
		}

	}

	// ligar paragens com o mesmo node
	for (unsigned int i = 0; i < map.getVertexSet().size(); i++){
		for (unsigned int j = 0; j < map.getVertexSet().size(); j++){
			if (j == i) continue;
			else{
				string stop_node1, stop_node2;
				stop_node1 = map.getVertexSet()[i]->getInfo().getNode();
				stop_node2 = map.getVertexSet()[j]->getInfo().getNode();

				if (stop_node1 == stop_node2){
					// PESO ??????????????
					map.addEdge(map.getVertexSet()[i]->getInfo(), map.getVertexSet()[j]->getInfo(), 0);
				}
			}
		}
	}
}

// Auxiliar Method
bool exists_in_vector(vector<string> v, string s){
	for (unsigned int i = 0; i < v.size(); i++)
		if (v[i] == s)
			return true;
	return false;
}

// Display alphabetically ordered graph
void NetworkMap::displayMap(){

	vector<string> visited_nodes;
	vector<string> to_output;

	for (unsigned int i = 0 ; i < map.getVertexSet().size() ; i++){

		if (exists_in_vector(visited_nodes, map.getVertexSet()[i]->getInfo().getNode())) continue;

		visited_nodes.push_back(map.getVertexSet()[i]->getInfo().getNode());
		string output;

		output += map.getVertexSet()[i]->getInfo().getName();
		output += " is connected to ";
		stringstream ss;
		ss << map.getVertexSet()[i]->getAdj().size();
		output += ss.str();
		output += " stop(s): \n";

		for (unsigned int j = 0; j < map.getVertexSet()[i]->getAdj().size(); j++){
			output += map.getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getName() + "\n";
		}

		output += "\n";
		to_output.push_back(output);

	}

	sort(to_output.begin(), to_output.end());
	for (unsigned int k = 0; k < to_output.size(); k++){
		cout << to_output[k];
	}

}
