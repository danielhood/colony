#include <memory>
#include <stdexcept>
#include "map/map.h"

using namespace std;

Map Map::getMap() {
	Map newMap = {};
	//newMap.generateTilesByRings();
	newMap.generateTilesByTraversal();
	return newMap;	
}


/// <summary>
/// Generate tiles by traversing all neighbours of starting tile.
/// Continue to generate tiles for a certain number of rings by 
/// visiting each and populating unlinked neighbours.
/// This process is repeatalbe for any given tile regardless of tile position on a ring.
/// This uses an (x,y) coorindate system where centroids of each tile have a coordinate 
/// where both x and y are either even or odd (e.g. (5,3) or (4,2) but not (5,2)).
/// This is used instead of (ring, pos).
/// </summary>
void Map::generateTilesByTraversal() {
	vector<Tile*> newTiles = {};

	// Create first tile
	Tile originTile = mapTiles_.emplace_back();
	newTiles.push_back(&originTile);

	originTile.setCoords(0, 0);

	if (MaxRings == 1) return;

	for (int r = 1; r < MaxRings; r++) {
		vector<Tile*> tilesToTraverse = newTiles;
		newTiles = {};

		for (Tile* t : tilesToTraverse) {
			// Check each link and populate if needed
			if (!t->links_[0]) {
				Tile* tile0 = &mapTiles_.emplace_back(); // TODO: this will update the storage of the vector objects, invalidating any pointers to the original storage. Use unique/shared pointers.
				newTiles.push_back(tile0);

				tile0->setCoords(t->getX(), t->getY() + 2);

				t->links_[0] = tile0;
				tile0->links_[3] = t;
			}

			if (!t->links_[1]) {
				Tile* tile1 = &mapTiles_.emplace_back();
				newTiles.push_back(tile1);

				tile1->setCoords(t->getX() + 1, t->getY() + 1);

				t->links_[1] = tile1;
				tile1->links_[4] = t;
			}

			if (!t->links_[2]) {
				Tile* tile2 = &mapTiles_.emplace_back();
				newTiles.push_back(tile2);

				tile2->setCoords(t->getX() + 1, t->getY() - 1);

				t->links_[2] = tile2;
				tile2->links_[5] = t;
			}

			if (!t->links_[3]) {
				Tile* tile3 = &mapTiles_.emplace_back();
				newTiles.push_back(tile3);

				tile3->setCoords(t->getX(), t->getY() - 2);

				t->links_[3] = tile3;
				tile3->links_[0] = t;

			}

			if (!t->links_[4]) {
				Tile* tile4 = &mapTiles_.emplace_back();
				newTiles.push_back(tile4);

				tile4->setCoords(t->getX()-1, t->getY() - 1);

				t->links_[4] = tile4;
				tile4->links_[1] = t;

			}

			if (!t->links_[5]) {
				Tile* tile5 = &mapTiles_.emplace_back();
				newTiles.push_back(tile5);

				tile5->setCoords(t->getX() - 1, t->getY() + 1);

				t->links_[5] = tile5;
				tile5->links_[2] = t;
			}

			// Update links between all neighbours
			t->links_[0]->links_[2] = t->links_[1];
			t->links_[1]->links_[5] = t->links_[0];

			t->links_[1]->links_[3] = t->links_[2];
			t->links_[2]->links_[0] = t->links_[1];

			t->links_[2]->links_[4] = t->links_[3];
			t->links_[3]->links_[1] = t->links_[2];

			t->links_[3]->links_[5] = t->links_[4];
			t->links_[4]->links_[2] = t->links_[3];

			t->links_[4]->links_[0] = t->links_[5];
			t->links_[5]->links_[3] = t->links_[4];

			t->links_[5]->links_[1] = t->links_[0];
			t->links_[0]->links_[4] = t->links_[5];
		}
	}
}


/// <summary>
/// Generate tiles by pre-populiting mapTiles_ in a speicfic ring traversal order.
/// Tiles are then linked in a group.
/// This uses a (ring,pos) coordinate system, insted of (x,y) centroids.
/// </summary>
void Map::generateTilesByRings() {
	// Generate all tiles for the map
	int currRing = 0;
	int currPos = 0;
	int lastIdx = totalNodesForRing(currRing) - 1;

	for (int i = 0; i < getMaxTiles(); ++i) {
		// Create tile
		mapTiles_.emplace_back();

		// Assign coordinates
		mapTiles_[i].setRingPos(currRing, currPos++);
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


/// <summary>
/// Old implementation that linked each tile travsering around the ring based on 
/// existing tiles addressable by (ring,pos) coordinates.
/// </summary>
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

Tile& Map::getTile(int ring, int pos) {
	if (ring >= MaxRings) {
		throw invalid_argument ("ring exceeds MaxRings");
	}

	if (pos >= ringSize(ring)) {
		throw invalid_argument ("pos exceeds size for given ring");
	}

	if (ring == 0) {
		return getCenterTile();
	}

	int tileIdx = totalNodesForRing(ring-1) + pos;

	return mapTiles_[tileIdx];
}
