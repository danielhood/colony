#include <stdexcept>
#include "map/tile.h"

using namespace std;

Tile::Tile() {
	links_[0] = NULL;
	links_[1] = NULL;
	links_[2] = NULL;
	links_[3] = NULL;
	links_[4] = NULL;
	links_[5] = NULL;
}

Tile& Tile::getLink(int index) {
	if (index >= dynLinks_.size()) {
		throw invalid_argument( "index references invalid link" );
	}

	return *dynLinks_[index];
}

void Tile::addLink(Tile& tile) {	
	if (dynLinks_.size() == 6 || tile.dynLinks_.size() == 6) {
		throw runtime_error( "attepting to add more than 6 tile links" );
	}

	dynLinks_.push_back(&tile);
	tile.dynLinks_.push_back(this);
}

bool Tile::isAdjacentTo(int ring, int pos) {
	for (int i=0; i< dynLinks_.size(); ++i) {
		if (dynLinks_[i]->getRing() == ring && dynLinks_[i]->getPos() == pos) {
			return true;
		}
	}

	return false;
}

void Tile::setRingPos(int ring, int pos) {
	if (coordInitialized_) {
		throw runtime_error( "attempted to reinitialize tile coordinate values (ring,pos)");
	}

	ring_ = ring; 
	pos_ = pos; 
	coordInitialized_ = true;
}

void Tile::setCoords(int x, int y) {
	if (coordInitialized_) {
		throw runtime_error("attempted to reinitialize tile coordinate values (x,y)");
	}

	x_ = x;
	y_ = y;
	
	coordInitialized_ = true;
}

