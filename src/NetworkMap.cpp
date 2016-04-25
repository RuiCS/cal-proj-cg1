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

        //cout << "Stop(" << name << ", " << lat << ", " << lon << ", " << node << ", " << zone << ", " << time << ");\n";

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
			map.addEdge(map.getVertexSet()[i]->getInfo(), map.getVertexSet()[i + 1]->getInfo(), map.getVertexSet()[i]->getInfo().calcTimeBetween(map.getVertexSet()[i + 1]->getInfo(), SUBWAY_VEL) + SUBWAY_INSTOP);
			map.addEdge(map.getVertexSet()[i + 1]->getInfo(), map.getVertexSet()[i]->getInfo(), map.getVertexSet()[i + 1]->getInfo().calcTimeBetween(map.getVertexSet()[i]->getInfo(), SUBWAY_VEL) + SUBWAY_INSTOP);
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
					map.addEdge(map.getVertexSet()[i]->getInfo(), map.getVertexSet()[j]->getInfo(), map.getVertexSet()[i]->getInfo().getWaitTime() * 60);
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
			stringstream double_strg;
			double_strg << map.getVertexSet()[i]->getAdj()[j].getWeight();
			output += map.getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getName() + ", " + double_strg.str() + "\n";
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
void graphView( NetworkMap nm){

	GraphViewer *gv = new GraphViewer(600, 600, false);


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
		} else if (line == " E"){
			x = 000; y = 400;
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


float NetworkMap::calcTimeBetween(const Stop &s1, const Stop &s2, int velocity, int timeInStops, vector<Stop> &stops){

	float time_elapsed = 0.0;

	vector<Stop> path;
	map.bellmanFordShortestPath(s1);
	path = map.getPath(s1, s2);
	stops = path;

	for (unsigned int i = 0; i < path.size() - 1; i++){
		if (round(path[i].calcTimeBetween(path[i+1], velocity)) == 0){
			time_elapsed += path[i+1].getWaitTime() * 60;
			cout << "PARAGEM " << path[i].getName() << " TO " << path[i+1].getName() << ". TIME TO ADD: " << path[i+1].getWaitTime() *60 << endl;
		}
		else{
			time_elapsed += path[i].calcTimeBetween(path[i+1], velocity) + timeInStops;
			cout << "PARAGEM " <<  path[i].getName() << " TO " << path[i+1].getName() << ". TIME TO ADD: " << path[i].calcTimeBetween(path[i+1], SUBWAY_VEL) << endl;
		}
	}

	return time_elapsed;

}

void NetworkMap::calcTimeBetweenStops(){

	string stop1_node, stop2_node;

	cout << "Insert the first stop's code: ";
	cin >> stop1_node;

	vector<Vertex<Stop>*> stops1, stops2;
	for (unsigned int i = 0; i < map.getVertexSet().size() ; i++){
		if (map.getVertexSet()[i]->getInfo().getNode() == stop1_node){
			stops1.push_back(map.getVertexSet()[i]);
		}
	}

	if (stops1.size() == 0){
		cout << "Not found..." << endl;
		return;
	}

	cout << "Insert the second stop's code: ";
	cin >> stop2_node;

	for (unsigned int i = 0; i < map.getVertexSet().size() ; i++){
		if (map.getVertexSet()[i]->getInfo().getNode() == stop2_node){
			stops2.push_back(map.getVertexSet()[i]);
		}
	}

	if (stops2.size() == 0){
		cout << "Not found..." << endl;
		return;
	}

	cout << endl;

	vector<Stop> stops;
	float time = 999999999;
	for (unsigned int i = 0; i < stops1.size(); i++){
		for (unsigned int j = 0; j < stops2.size(); j++){
			vector <Stop> temp_vector;
			float temp = calcTimeBetween(stops1[i]->getInfo(), stops2[j]->getInfo(), SUBWAY_VEL, SUBWAY_INSTOP, temp_vector);
			if (temp < time){
				time = temp;
				stops = temp_vector;
			}
		}
	}

	cout << "Itinerary: " << endl;

	for (unsigned int i = 0; i < stops.size(); i++){
		cout << stops[i].getName() << endl;
	}

	if (time >= 3600){
		int time_hours, time_minutes;
		time_hours = time / 3600;
		time_minutes = round((time / 3600) / 60);
		cout << "Time between stops: " << time_hours << " hours, " << time_minutes << " minutes." << endl;
	}
	else{
		int time_minutes = round(time / 60);
		cout << "Time between stops: " << time_minutes << " minutes." << endl;
	}

	cout << endl;
}

// Calculate number of line/transport switches
int NetworkMap::calcNumberOfLineSwitchesBetween(const Stop &s1, const Stop &s2, vector<Stop> &stops){

	vector<string> lines;

	vector<Stop> path;
	map.bellmanFordShortestPath(s1);
	path = map.getPath(s1, s2);
	stops = path;

	for (unsigned int i = 0; i < path.size(); i++){
		string line, name, trash;
		stringstream ss(path[i].getName());
		getline(ss, name, '-');
		ss >> line;
		if (!exists_in_vector(lines, line)){
			if (lines.size() != 0){
				cout << "Switch from line " << lines[lines.size()-1] << " to line " << line << " at " << name << endl;
			}
			lines.push_back(line);
		}
	}

	return lines.size() - 1;

}

void NetworkMap::calcSwitchesBetweenStops(){

	string stop1_node, stop2_node;

	cout << "Insert the first stop's code: ";
	cin >> stop1_node;

	Stop s1(stop1_node);

	vector<Vertex<Stop>*> stops1, stops2;
	for (unsigned int i = 0; i < map.getVertexSet().size() ; i++){
		if (map.getVertexSet()[i]->getInfo().getNode() == stop1_node){
			stops1.push_back(map.getVertexSet()[i]);
		}
	}

	if (stops1.size() == 0){
		cout << "Not found..." << endl;
		return;
	}

	cout << "Insert the second stop's code: ";
	cin >> stop2_node;

	for (unsigned int i = 0; i < map.getVertexSet().size() ; i++){
		if (map.getVertexSet()[i]->getInfo().getNode() == stop2_node){
			stops2.push_back(map.getVertexSet()[i]);
		}
	}

	if (stops2.size() == 0){
		cout << "Not found..." << endl;
		return;
	}

	cout << endl;
	vector<Stop> stops;
	int switches = 999999999;
	for (unsigned int i = 0; i < stops1.size(); i++){
		for (unsigned int j = 0; j < stops2.size(); j++){
			vector <Stop> temp_vector;
			int temp = calcNumberOfLineSwitchesBetween(stops1[i]->getInfo(), stops2[j]->getInfo(), temp_vector);
			if (temp < switches){
				switches = temp;
				stops = temp_vector;
			}
		}
	}

	cout << "Itinerary: " << endl;

	for (unsigned int i = 0; i < stops.size(); i++){
		cout << stops[i].getName() << endl;
	}

	cout << "Number of switches: " << switches << endl;
	cout << endl;
}

