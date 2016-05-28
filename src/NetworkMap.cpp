#include "NetworkMap.h"
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "matcher.h"

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
	for (unsigned int i = 0; i < vertexSet.size() ; i++){
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

	float lonDiff = MAX_LON - MIN_LON;
	float latDiff = MAX_LAT - MIN_LAT;

	gv->defineVertexSize(40);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->defineEdgeCurved(false);

	int edgeID = 0;

	for (unsigned int i = 0; i < nm.getMap().getVertexSet().size(); i++){
		stringstream liness(nm.getMap().getVertexSet()[i]->getInfo().getName());
		string trash, line;
		getline(liness, trash, '-');
		getline(liness, line);
		int x, y, offset;
		if (line == " C"){
			offset = 100;
		} else if (line == " D"){
			offset = 100;
		} else if (line == " F"){
			offset = 200;
		} else if (line == " E"){
			offset = 300;
		}

		x = (int)((MAX_LON - nm.getMap().getVertexSet()[i]->getInfo().getLongitude())/(lonDiff) * WIN_WIDTH);
		y = (int)((MAX_LAT - nm.getMap().getVertexSet()[i]->getInfo().getLatitude())/(latDiff) * WIN_HEIGHT);

		gv->addNode(i, x - 500, y + offset - 500);
		stringstream lbl;
		lbl << "(" << nm.getMap().getVertexSet()[i]->getInfo().getNode() << ") " << nm.getMap().getVertexSet()[i]->getInfo().getName();
		gv->setVertexLabel(i, lbl.str());
	}

	for (unsigned int j = 0; j < nm.getMap().getVertexSet().size(); j++){
		for (unsigned int k = 0; k < nm.getMap().getVertexSet()[j]->getAdj().size(); k++){

			int indice = findVertexInVector(nm.getMap().getVertexSet(), nm.getMap().getVertexSet()[j]->getAdj()[k].getDest());
			if (indice != -1){
				gv->addEdge(edgeID, j, indice, EdgeType::DIRECTED);

				if (nm.getMap().getVertexSet()[j]->getInfo().getNode() == nm.getMap().getVertexSet()[indice]->getInfo().getNode()) {
					gv->setEdgeDashed(edgeID, true);
				}

				//stringstream double_strg;
				//double_strg << nm.getMap().getVertexSet()[j]->getAdj()[k].getWeight();
				//gv->setEdgeLabel(edgeID, double_strg.str());
				edgeID++;
			}
		}
	}

	Sleep(2000);

	gv->rearrange();
}

// Finds the weight of a path
float NetworkMap::pathWeight(const Stop& s1, const Stop& s2) {
	float weight = 0;
	vector<Stop> path = map.getPath(s1, s2);
	for (unsigned int i = 0; i < path.size() - 1; i++) {
		int index = -1;
		for (unsigned int j = 0; j < map.getVertexSet().size(); j++) {
			if (map.getVertexSet()[j]->getInfo().getName() == path[i].getName())
				index = j;
		}
		for (unsigned int k = 0; k < map.getVertexSet()[index]->getAdj().size(); k++) {
			if (map.getVertexSet()[index]->getAdj()[k].getDest()->getInfo().getName() == path[i+1].getName())
				weight += map.getVertexSet()[index]->getAdj()[k].getWeight();
		}
	}
	return weight;
}

vector<Stop> NetworkMap::findLightestPath(string s1, string s2, float &weight) {
	vector<Stop> beginStops, endStops;
	vector<vector<Stop> > paths;
	float lightestPathWeight = 999999.0;
	int lightestPathIndex = -1;

	for (unsigned int i = 0; i < map.getVertexSet().size(); i++) {
		if (map.getVertexSet()[i]->getInfo().getNode() == s1)
			beginStops.push_back(map.getVertexSet()[i]->getInfo());
		if (map.getVertexSet()[i]->getInfo().getNode() == s2)
			endStops.push_back(map.getVertexSet()[i]->getInfo());
	}

	if (beginStops.size() == 0 || endStops.size() == 0) {
		cout << "ERRO : Pelo menos uma das paragens não existe! " << endl << endl;
		vector<Stop> err;
		return err;
	}


	for (unsigned int j = 0; j < beginStops.size(); j++) {
		map.dijkstraShortestPath(beginStops[j]);
		for (unsigned int k = 0; k < endStops.size(); k++) {
			paths.push_back(map.getPath(beginStops[j], endStops[k]));
			if (pathWeight(beginStops[j], endStops[k]) < lightestPathWeight) {
				lightestPathWeight = pathWeight(beginStops[j], endStops[k]);
				lightestPathIndex = paths.size() - 1;
			}
		}
	}

	weight = lightestPathWeight;
	return paths[lightestPathIndex];
}

void NetworkMap::findFastestPath(string s1, string s2) {
	float weight = 0;
	resetEdges(&timeWeight, *this);
	vector<Stop> path = findLightestPath(s1, s2, weight);

	if (path.size() == 0) return;
	cout << endl << "ITINERARIO A PERCORRER:" << endl;
	for (unsigned int i = 0; i < path.size(); i++) {
		cout << path[i].getName() << endl;
	}
	cout << "TEMPO DE VIAGEM: " << weight / 60 << " min " << endl << endl;
}

void NetworkMap::findCheapestPath(string s1, string s2) {
	float weight = 0;
	resetEdges(&priceWeight, *this);
	vector<Stop> path = findLightestPath(s1, s2, weight);

	if (path.size() == 0) return;
	cout << endl << "ITINERARIO A PERCORRER:" << endl;
	for (unsigned int i = 0; i < path.size(); i++) {
		cout << path[i].getName() << endl;
	}
	cout << "PRECO DA VIAGEM: " << calcPrice((int)weight) << "eur ( " << weight  << " ZONA(S) )" << endl << endl;
}

void NetworkMap::findShortestPath(string s1, string s2) {
	float weight = 0;
	resetEdges(&distanceWeight, *this);
	vector<Stop> path = findLightestPath(s1, s2, weight);

	if (path.size() == 0) return;
	cout << endl << "ITINERARIO A PERCORRER:" << endl;
	for (unsigned int i = 0; i < path.size(); i++) {
		cout << path[i].getName() << endl;
	}
	cout << "DISTANCA PERCORRIDA: " << weight/1000 << " km" << endl << endl;
}

void NetworkMap::findLeastLineSwitchesPath(string s1, string s2) {
	float weight = 0;
	resetEdges(&lineSwitchWeight, *this);
	vector<Stop> path = findLightestPath(s1, s2, weight);

	if (path.size() == 0) return;
	cout << endl << "ITINERARIO A PERCORRER:" << endl;
	for (unsigned int i = 0; i < path.size(); i++) {
		cout << path[i].getName() << endl;
	}
	cout << "NUMERO DE TRANSBORDOS: " << weight << endl << endl;
}

void NetworkMap::getArt(){
	int counter=1;
	cout<<"Pontos de articulação:\n";
	vector<Stop> res;
	res=map.findArt();
	for(int i=0;i<res.size();i++){
		cout<<res[i].getName()<< "\n";
	}
	cout<<"\n";
}

string NetworkMap::getStopsString(){
	string retorno;
	for (int i = 0; i < map.getNumVertex(); i++){
		retorno +=  map.getVertexSet()[i]->getInfo().getName() + "\n";
	}
	return retorno;
}

int NetworkMap::stopExists(string stopName){
	string stopNames = getStopNames(getStopsString());
	int retorno = kmp(stopNames, stopName);
	return retorno;
}

bool NetworkMap::stopExistsInLine(string stopName){
	int nTimes = stopExists(stopName);
	if (nTimes == 0){
		cout << "Paragem não encontrada! Será que quis dizer..." << endl;
		vector<string> similarStops = getSimilarStops(stopName, getStopNames(getStopsString()), 3);
		for (unsigned int i = 0; i < similarStops.size(); i++){
			cout << similarStops[i] << "?" << endl;
		}
		return false;
	}
	else{
		cout << "Paragem encontrada nas linhas: " << endl;
		vector<string> lines = getLinesForName(stopName, getStops());
		for (unsigned int i = 0; i < lines.size(); i++){
			cout << lines[i] << endl;
		}
		return true;
	}
	return false;

}

vector<Stop> NetworkMap::getStops(){
	vector<Stop> retorno;

	for (int i = 0; i < getMap().getVertexSet().size(); i++){
		retorno.push_back(getMap().getVertexSet()[i]->getInfo());
	}

	return retorno;
}

// Resets the edges and recalculates the edge weight according to a weight function
void resetEdges(float(*weightFunction)(const Stop&, const Stop&), NetworkMap &nm) {
	for (unsigned int i = 0; i < nm.getMap().getVertexSet().size(); i++) {
		for (unsigned int j = 0; j < nm.getMap().getVertexSet().size(); j++) {
			if (i == j) continue;
			nm.getMap().removeEdge(nm.getMap().getVertexSet()[i]->getInfo(), nm.getMap().getVertexSet()[j]->getInfo());
		}
	}

	// pressupondo que as paragens estao por ordem no ficheiro...
	for (unsigned int i = 0; i < nm.getMap().getVertexSet().size() - 1; i++){

		string stop_name1, stop_name2;
		stop_name1 = nm.getMap().getVertexSet()[i]->getInfo().getName();
		stop_name2 = nm.getMap().getVertexSet()[i + 1]->getInfo().getName();

		stringstream st1(stop_name1);
		stringstream st2(stop_name2);
		string trash, line1, line2;

		// nome - linha
		getline(st1, trash, '-');
		getline(st1, line1);
		getline(st2, trash, '-');
		getline(st2, line2);

		if (line1 == line2){
			nm.getMap().addEdge(nm.getMap().getVertexSet()[i]->getInfo(), nm.getMap().getVertexSet()[i + 1]->getInfo(), (*weightFunction)(nm.getMap().getVertexSet()[i]->getInfo(), nm.getMap().getVertexSet()[i + 1]->getInfo()));
			nm.getMap().addEdge(nm.getMap().getVertexSet()[i + 1]->getInfo(), nm.getMap().getVertexSet()[i]->getInfo(), (*weightFunction)(nm.getMap().getVertexSet()[i]->getInfo(), nm.getMap().getVertexSet()[i + 1]->getInfo()));
		}

	}

	// ligar paragens com o mesmo node
	for (unsigned int i = 0; i < nm.getMap().getVertexSet().size(); i++){
		for (unsigned int j = 0; j < nm.getMap().getVertexSet().size(); j++){
			if (j == i) continue;
			else{
				string stop_node1, stop_node2;
				stop_node1 = nm.getMap().getVertexSet()[i]->getInfo().getNode();
				stop_node2 = nm.getMap().getVertexSet()[j]->getInfo().getNode();

				if (stop_node1 == stop_node2){
					nm.getMap().addEdge(nm.getMap().getVertexSet()[i]->getInfo(), nm.getMap().getVertexSet()[j]->getInfo(), (*weightFunction)(nm.getMap().getVertexSet()[i]->getInfo(), nm.getMap().getVertexSet()[j]->getInfo()));
				}
			}
		}
	}
}

// Weight Functions -----------------------------------------------------------------------------

float timeWeight(const Stop& s1, const Stop& s2) {
	if (s1.getNode() == s2.getNode())
		return s1.getWaitTime() * 60;

	return s1.calcTimeBetween(s2, SUBWAY_VEL) + SUBWAY_INSTOP;
}

float priceWeight(const Stop& s1, const Stop& s2) {
	if (s1.getZone() == s2.getZone())
		return 0;
	return 1;
}

float distanceWeight(const Stop& s1, const Stop &s2) {
	return s1.calcDistance(s2);
}

float lineSwitchWeight(const Stop& s1, const Stop &s2) {
	if (s1.getLine() == s2.getLine())
		return 0;
	return 1;
}

// Auxiliary function
float calcPrice(int numZones) {
	float price = 1.20;
	switch(numZones) {
	case 3:
		price = 1.50;
		break;
	case 4:
		price = 1.85;
		break;
	case 5:
		price = 2.30;
		break;
	case 6:
		price = 2.70;
		break;
	case 7:
		price = 3.05;
		break;
	case 8:
		price = 3.45;
		break;
	case 9:
		price = 3.80;
		break;
	case 10:
		price = 4.20;
		break;
	case 11:
		price = 4.60;
		break;
	case 12:
		price = 5.00;
		break;
	}
	return price;
}

string getStopNames(string stops){
	string retorno, line;
	stringstream ss(stops);
	while(getline(ss, line)){
		stringstream name(line);
		string stopName;
		while (!name.eof())
		{
			name >> stopName;
			if (stopName == "-")
				break;
			else retorno += stopName + " ";
		}
		retorno += "\n";

	}
	return retorno;
}

string getStopLines(string stops){
	string retorno, line;
	stringstream ss(stops);
	while(getline(ss, line)){
		stringstream name(line);
		string stopLine;
		while (!name.eof())
		{
			name >> stopLine;
			if (stopLine != "-")
				continue;
			else {
				name >> stopLine;
				retorno += stopLine;
			}
		}
		retorno += "\n";

	}
	return retorno;
}

vector<string> getSimilarStops(string stop, string stops, int distance){
	vector<string> retorno;
	stringstream ss(stops);
	string line;
	while (!ss.eof()){
		getline(ss, line);
		int dis = editDistance(stop, line);
		if (dis <= distance && !exists_in_vector(retorno, line))
			retorno.push_back(line);
	}
	return retorno;
}

vector<string> getLinesForName(string stopName, vector<Stop> stops){
	vector<string> retorno;
	for (int i = 0; i < stops.size(); i++){

		stringstream stop(stops[i].getName());
		string selectedStopName;
		string nameToCompare;
		while (!stop.eof()){
			stop >> selectedStopName;
			if (selectedStopName == "-") break;
			else nameToCompare += selectedStopName + " ";
		}
		if (nameToCompare.substr(0, nameToCompare.length() - 1) == stopName){
			retorno.push_back(stops[i].getLine());
		}
	}
	return retorno;
}
