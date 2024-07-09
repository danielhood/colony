#include <memory>
#include <stdexcept>
#include "map/map.h"

using namespace std;

Map Map::getMap() {
	Map newMap = {};
	newMap.generateTiles(MaxRings);
	return newMap;	
}


/// <summary>
/// Generate tiles by traversing all neighbours of starting tile.
/// Continue to generate tiles for a certain number of rings by 
/// visiting each and populating unlinked neighbours.
/// </summary>
void Map::generateTiles(int numRings) {
	vector<shared_ptr<Tile>> newTiles = {};

	// Create first tile
	auto originTile = make_shared<Tile>();
	mapTiles_.push_back(originTile);
	newTiles.push_back(originTile);

	originTile->setCoords(0, 0);

	// numRings = 0 generates only the starting tile
	if (numRings == 0) return;

	for (int r = 1; r <= numRings; r++) {
		vector<shared_ptr<Tile>> tilesToTraverse = newTiles;
		newTiles.clear();

		for (auto t : tilesToTraverse) {
			generateImmediateNeighbours(t, newTiles);
		}
	}
}

/// <summary>
/// Generate and link all 6 immediate neighbours of the given tile.
/// This handles tiles with parital sets of neighbours, resulting with a full set of 6 neighbours.
/// This process is repeatalbe for any given tile regardless of tile position on a ring.
/// This uses an (x,y) coorindate system where centroids of each tile have a coordinate 
/// where both x and y are either even or odd (e.g. (5,3) or (4,2) but not (5,2)).
/// </summary>
/// <param name="t"></param>
/// <param name="newTiles"></param>
void Map::generateImmediateNeighbours(shared_ptr<Tile> t, vector<shared_ptr<Tile>> &newTiles)
{
	// Check each link and populate if needed
	if (!t->links_[0]) {
		auto tile0 = generateTile(newTiles);

		tile0->setCoords(t->getX(), t->getY() + 2);

		t->links_[0] = tile0;
		tile0->links_[3] = t;
	}

	if (!t->links_[1]) {
		auto tile1 = generateTile(newTiles);

		tile1->setCoords(t->getX() + 1, t->getY() + 1);

		t->links_[1] = tile1;
		tile1->links_[4] = t;
	}

	if (!t->links_[2]) {
		auto tile2 = generateTile(newTiles);

		tile2->setCoords(t->getX() + 1, t->getY() - 1);

		t->links_[2] = tile2;
		tile2->links_[5] = t;
	}

	if (!t->links_[3]) {
		auto tile3 = generateTile(newTiles);

		tile3->setCoords(t->getX(), t->getY() - 2);

		t->links_[3] = tile3;
		tile3->links_[0] = t;
	}

	if (!t->links_[4]) {
		auto tile4 = generateTile(newTiles);

		tile4->setCoords(t->getX() - 1, t->getY() - 1);

		t->links_[4] = tile4;
		tile4->links_[1] = t;
	}

	if (!t->links_[5]) {
		auto tile5 = generateTile(newTiles);

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


/// <summary>
/// Generate a single tile on the tile pool
/// </summary>
/// <returns></returns>
shared_ptr<Tile> Map::generateTile(vector<shared_ptr<Tile>> &newTiles)
{
	auto tile = make_shared<Tile>();
	mapTiles_.push_back(tile);
	newTiles.push_back(tile);

	return tile;
}

Tile& Map::getCenterTile()
{
	return *mapTiles_[0];
}

Tile& Map::getTile(int x, int y) {
	for (auto t : mapTiles_) {
		if (t->getX() == x && t->getY() == y)
			return *t;
	}

	throw invalid_argument("invalid ring coordinates");
}