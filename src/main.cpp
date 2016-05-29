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
		cout << "7 - Econtrar pontos de articulação " << endl;
		cout << "8 - Encontrar paragem" << endl;
		cout << "10 - Sair " << endl;
		cout << "> "; cin >> option;
		switch(option){
		case 1:	graphView(nm); break;
		case 2: nm.displayMap(); break;
		case 3:
			cout << "Paragem 1 ? "; cin.ignore(); getline(cin, s1);
			cout << "Paragem 2 ? "; cin.ignore(); getline(cin, s2);
			nm.findFastestPath(nm.stopNameConverter(s1), nm.stopNameConverter(s2));
			break;
		case 4:
			cout << "Paragem 1 ? "; cin.ignore(); getline(cin, s1);
			cout << "Paragem 2 ? "; cin.ignore(); getline(cin, s2);
			nm.findCheapestPath(nm.stopNameConverter(s1), nm.stopNameConverter(s2));
			break;
		case 5:
			cout << "Paragem 1 ? "; cin.ignore(); getline(cin, s1);
			cout << "Paragem 2 ? "; cin.ignore(); getline(cin, s2);
			nm.findShortestPath(nm.stopNameConverter(s1), nm.stopNameConverter(s2));
			break;
		case 6:
			cout << "Paragem 1 ? "; cin.ignore(); getline(cin, s1);
			cout << "Paragem 2 ? "; cin.ignore(); getline(cin, s2);
			nm.findLeastLineSwitchesPath(nm.stopNameConverter(s1), nm.stopNameConverter(s2));
			break;
		case 7:
			nm.getArt();
			break;
		case 8:
			cout << "\nNome da Paragem ? "; cin.ignore(); getline(cin, s1);
			nm.stopExistsInLine(s1);
			break;
		case 9:
			cout << "Saindo..." << endl;
			exit(0);
			break;
		default: exit(1); break;
		}
	}

}

int main(void) {

	runInterface();
	return 0;
}
