#include "NetworkMap.h"
#include <algorithm>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

// Auxiliary Method for graphView()
int findVertexInVector(vector <Vertex<Stop>*> vertexSet, Vertex<Stop>* to_find){
	for (int i = 0; i < vertexSet.size() ; i++){
		if (to_find->getInfo().getName() == vertexSet[i]->getInfo().getName()){
			return i;
		}
	}
	return -1;
}

// Display Graph with GraphViewer
void graphView(){

	GraphViewer *gv = new GraphViewer(600, 600, false);

	NetworkMap nm = NetworkMap();
	nm.loadMap("input.txt");
	nm.setConnections();

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	int edgeID = 0;

	for (unsigned int i = 0; i < nm.getMap().getVertexSet().size(); i++){
		stringstream liness(nm.getMap().getVertexSet()[i]->getInfo().getName());
		string trash, line;
		getline(liness, trash, '-');
		getline(liness, line);
		int x = 100, y = 0;
		if (line == " C"){
			x = 100; y = 100;
		} else if (line == " D"){
			x = 100; y = 200;
		} else if (line == " F"){
			x = 100; y = 300;
		}
		gv->addNode(i, x + i * 20, y );
		gv->setVertexLabel(i, nm.getMap().getVertexSet()[i]->getInfo().getName());
	}

	for (unsigned int j = 0; j < nm.getMap().getVertexSet().size(); j++){
		for (unsigned int k = 0; k < nm.getMap().getVertexSet()[j]->getAdj().size(); k++){

			int indice = findVertexInVector(nm.getMap().getVertexSet(), nm.getMap().getVertexSet()[j]->getAdj()[k].getDest());
			if (indice != -1){
				gv->addEdge(edgeID, j, indice, EdgeType::DIRECTED);
				stringstream double_strg;
				double_strg << nm.getMap().getVertexSet()[j]->getAdj()[k].getWeight();
				gv->setEdgeLabel(edgeID, double_strg.str());
				edgeID++;
			}
		}
	}

	Sleep(2000);

	gv->rearrange();


}
