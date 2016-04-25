#include "NetworkMap.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void runInterface(){

	int option;
	string s1, s2;

	cout << "Bem Vindo ao TripPlanner!" << endl;
	NetworkMap nm = NetworkMap();
	nm.loadMap("input.txt");
	resetEdges(&distanceWeight, nm);

	while (true){
		cout << "Escolhe uma opcao: " << endl;
		cout << "1 - Mostrar grafo com GraphViewer" << endl;
		cout << "2 - Mostrar grafo em texto" << endl;
		cout << "3 - Encontrar caminho mais rápido" << endl;
		cout << "4 - Encontrar caminho mais barato" << endl;
		cout << "5 - Encontrar caminho mais curto" << endl;
		cout << "6 - Encontrar caminho com menos transbordos" << endl;
		cout << "7 - Sair " << endl;
		cout << "> "; cin >> option;
		switch(option){
		case 1:	graphView(nm); break;
		case 2: nm.displayMap(); break;
		case 3:
			cout << "STOP1 STOP2 ? "; cin >> s1 >> s2;
			nm.findFastestPath(s1, s2);
			break;
		case 4:
			cout << "STOP1 STOP2 ? "; cin >> s1 >> s2;
			nm.findCheapestPath(s1, s2);
			break;
		case 5:
			cout << "STOP1 STOP2 ? "; cin >> s1 >> s2;
			nm.findShortestPath(s1, s2);
			break;
		case 6:
			cout << "STOP1 STOP2 ? "; cin >> s1 >> s2;
			nm.findLeastLineSwitchesPath(s1, s2);
			break;
		case 7: cout << "Saindo..." << endl; exit(0); break;
		default: exit(1); break;
		}
	}

}

int main(void) {

	runInterface();
	return 0;
}
