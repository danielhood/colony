#include <stdexcept>
#include "map/tile.h"

using namespace std;

Tile& Tile::getLink(int index) {
	if (index >= links_.size()) {
		throw invalid_argument( "index references invalid link" );
	}

	return *links_[index];
}

void Tile::addLink(Tile& tile) {	
	if (links_.size() == 6 || tile.links_.size() == 6) { 
		throw runtime_error( "attepting to add more than 6 tile links" );
	}

	links_.push_back(&tile);
	tile.links_.push_back(this);
}

void Tile::setCoord (int ring, int pos) { 
	if (coordInitialized_) {
		throw runtime_error( "attempted to reinitialize tile coordinate values");
	}

	ring_ = ring; 
	pos_ = pos; 
	coordInitialized_ = true;
}

