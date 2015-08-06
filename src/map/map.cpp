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
	for (int i=0; i<getMaxTiles(); ++i) {		
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
		//mapTiles_[i+1].addLink(mapTiles_[0]);

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
	//

	int currOuterRing = 2;
	int currOuterRingSize = ringSize(currOuterRing);

	auto innerTileItr = getRingStart(startTile);
	auto outerTileItr = getRingEnd(startTile)+1;

	auto innerRingStart = getRingStart(startTile); 

	// Set coordinates for current outer ring
	for (int i = 0; i < currOuterRingSize; ++i) {
		(outerTileItr+i)->setCoord(currOuterRing, i);
	}
	
	while (outerTileItr != mapTiles_.end()) {
		if (isKeyNode(*innerTileItr)) {
			innerTileItr->addLink(*outerTileItr);
			outerTileItr++;
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
			if (outerTileItr != mapTiles_.end()) {
				// Set coordinates for current outer ring
				for (int i = 0; i < currOuterRingSize; ++i) {
					(outerTileItr+i)->setCoord(currOuterRing, i);
				}
			}
		} else {
			innerTileItr->addLink(*(innerTileItr + 1));
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

