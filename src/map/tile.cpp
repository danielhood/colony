#include <stdexcept>
#include "map/tile.h"

using namespace std;

Tile& Tile::getLink(int index) {
	if (index >= 6) {
		throw invalid_argument( "index references invalid link" );
	}

	return *links_[index];
}

bool Tile::isAdjacentTo(int x, int y) {
	for (int i=0; i<6; ++i) {
		if (!links_[i]) continue;

		if (links_[i]->getX() == x && links_[i]->getY() == y) {
			return true;
		}
	}

	return false;
}

void Tile::setCoords(int x, int y) {
	if (coordInitialized_) {
		throw runtime_error("attempted to reinitialize tile coordinate values (x,y)");
	}

	x_ = x;
	y_ = y;
	
	coordInitialized_ = true;
}

