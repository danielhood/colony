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
	int currRing = 0;
	int currPos = 0;
	int lastIdx = totalNodesForRing(currRing) - 1;

	for (int i = 0; i < getMaxTiles(); ++i) {
		// Create tile
		mapTiles_.emplace_back();

		// Assign coorinates
		mapTiles_[i].setCoord(currRing, currPos++);
		if (i == lastIdx) {
			lastIdx = totalNodesForRing(++currRing) - 1;
			currPos = 0;
		}
	}

	// Generate links between all nodes
	linkRings();
}

void Map::linkFirstRing() {
	for (int i = 0; i < 6; ++i) {
		// Link (0,0) to ring 1
		getCenterTile().addLink(mapTiles_[i+1]);
	}
}

void Map::linkRings() {
	// Build up coordinates and links for rings 0 to MaxRings 
	// Nodes on the outer ring will have less than 6 links
	// This ensures that all links are traverable

	linkFirstRing();

	Tile startTile = mapTiles_[1];

	int currOuterRing = startTile.getRing()+1;
	int currOuterRingSize = ringSize(currOuterRing);

	auto innerTileItr = getRingStart(startTile);
	auto outerTileItr = getRingEnd(startTile)+1;
	auto innerRingStart = innerTileItr; 

	while (outerTileItr != mapTiles_.end()) {
		// Handle special case to add links between key nodes
		if (isKeyNode(*innerTileItr)) {
			if (!isKeyNode(*outerTileItr)) {
				throw runtime_error( "outer tile not keynode when linked from inner keynode" );
			}
			innerTileItr->addLink(*outerTileItr);
			++outerTileItr;
		}
		
		innerTileItr->addLink(*outerTileItr);

		if ((innerTileItr + 1)->getRing() == outerTileItr->getRing()) {
			// We are about to jump up a ring
			innerTileItr->addLink(*innerRingStart);
			innerRingStart->addLink(*outerTileItr);
			innerRingStart = ++innerTileItr;
			++outerTileItr;
			++currOuterRing;
			currOuterRingSize = ringSize(currOuterRing);
		} else {
			innerTileItr->addLink(*(innerTileItr+1));
			++innerTileItr;
			innerTileItr->addLink(*outerTileItr);
			++outerTileItr;
		}
	}
}

Tile& Map::getCenterTile()
{
	return mapTiles_[0];
}

