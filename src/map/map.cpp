#include <memory>
#include "map/map.h"

using namespace std;

Map Map::getMap() {
			Map newMap = {};
			newMap.generateTiles();
			return newMap;	
}

void Map::generateTiles() {
	// Generate all tiles for the map
	for (int i=0; i<MaxTiles; ++i) {		
		mapTiles_.emplace_back();
	}

	// Add links for center and first ring
	linkFirstRing();

	// Link rings starting from Tile(1,0)
	linkRings(mapTiles_[1]);
}

void Map::linkFirstRing() {
	for (int i=0; i<6; ++i) {
		// Link (0,0) to ring 1
		getCenterTile().addLink(mapTiles_[i+1]);

		// Set backlink to center tile
		mapTiles_[i+1].addLink(mapTiles_[0]);

		// Set tile coordinates (ring, node)
		mapTiles_[i+1].setCoord(1, i);
	}

	// set coord of centerTile to (0,0)
	getCenterTile().setCoord(0, 0);
}

void Map::linkRings(Tile& startTile) {
	// TODO: spiral outwards building links for remaining map
	// TODO: currently we are not peserving expclit link indexes for specific 'directions'
	// TODO: need to figure out how we are going to termintate the outbond links for the last ring 
}

Tile& Map::getCenterTile()
{
	return mapTiles_[0];
}

