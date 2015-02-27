#include <iostream>
#include <utility>
#include "map/map.h"

using namespace std;

int main(int argc, char **argv) {
	cout << "colony v1.0.0" << endl;

	Map map = Map::getMap();
	cout << "numTiles: " << map.numTiles() << endl;

	return 0;

}
