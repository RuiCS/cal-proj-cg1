#include "NetworkMap.h"

#include <iostream>
#include <iomanip>

using namespace std;

bool exists_in_vector(vector<string> v, string s){
	for (int i = 0; i < v.size(); i++)
		if (v[i] == s)
			return true;
	return false;
}

int main(void) {
	NetworkMap nm = NetworkMap();
	nm.loadMap("input.txt");
	nm.setConnections();

	vector<string> visited_nodes;

	for (int i = 0 ; i < nm.getMap().getVertexSet().size() ; i++){
			if (exists_in_vector(visited_nodes, nm.getMap().getVertexSet()[i]->getInfo().getNode())) continue;
			visited_nodes.push_back(nm.getMap().getVertexSet()[i]->getInfo().getNode());
			cout << nm.getMap().getVertexSet()[i]->getInfo().getName();
			cout << " is connected to " << nm.getMap().getVertexSet()[i]->getAdj().size() << " stop(s): " << endl;
			for (int j = 0; j < nm.getMap().getVertexSet()[i]->getAdj().size(); j++){
				cout << nm.getMap().getVertexSet()[i]->getAdj()[j].getDest()->getInfo().getName() << endl;
			}
			cout << endl;
	}

	return 0;
}
