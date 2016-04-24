#include "NetworkMap.h"

#include <iostream>
#include <iomanip>

using namespace std;

int main(void) {

	NetworkMap nm = NetworkMap();
	nm.loadMap("input.txt");
	nm.setConnections();
	graphView(nm);
	nm.displayMap();
	nm.calcTimeBetweenStops();

	return 0;
}
