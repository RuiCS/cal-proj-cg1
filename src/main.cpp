#include "NetworkMap.h"

#include <iostream>

using namespace std;

int main(void) {
	NetworkMap nm = NetworkMap();
	nm.loadMap("input.txt");

	return 0;
}
