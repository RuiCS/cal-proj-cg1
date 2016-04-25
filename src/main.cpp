#include "NetworkMap.h"

#include <iostream>
#include <iomanip>

using namespace std;

float test() {
	return 2.4;
}

void runInterface(){

	int option;

	cout << "Welcome." << endl;

	cout << "1 - Load from file" << endl;
	cout << "2 - Quit" << endl;

	cin >> option;
	NetworkMap nm;
	switch(option){
	case 1: {
		nm = NetworkMap();
		nm.loadMap("input.txt");
		resetEdges(&priceWeight, nm);
		break;
	}
	case 2: exit(0); break;
	default: exit(1); break;
	}


	while (true){
		cout << "1 - Display Graph with GraphViewer" << endl;
		cout << "2 - Display Graph in text" << endl;
		cout << "3 - Time between..." << endl;
		cout << "4 - Line Switches between..." << endl;
		cout << "5 - Quit" << endl;
		cin >> option;
		switch(option){
		case 1:	graphView(nm); break;
		case 2: nm.displayMap(); break;
		case 3: nm.calcTimeBetweenStops(); break;
		case 4: nm.calcSwitchesBetweenStops(); break;
		case 5: exit(0); break;
		default: exit(1); break;
		}
	}

}

int main(void) {

	runInterface();
	return 0;
}
