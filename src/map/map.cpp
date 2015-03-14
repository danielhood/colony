#include <memory>
#include "map/map.h"

using namespace std;

Map Map::getMap() {
			Map newMap = {};
			newMap.generateTiles();
			return newMap;	
}

void Map::generateTiles() {
	for (int i=0; i<MaxTiles; ++i) {		
		mapTiles_.emplace_back();
	}

	mapTiles_[0].Links.push_back(ref<Tile>(mapTiles_[1]));
	mapTiles_[0].Links.push_back(ref<Tile>(mapTiles_[2]));
	mapTiles_[0].Links.push_back(ref<Tile>(mapTiles_[3]));
	mapTiles_[0].Links.push_back(ref<Tile>(mapTiles_[4]));
	mapTiles_[0].Links.push_back(ref<Tile>(mapTiles_[5]));
	mapTiles_[0].Links.push_back(ref<Tile>(mapTiles_[6]));

	Tile& tile = mapTiles_[0].Links[0];
	tile.setId(1);
	//cout << tile.getId() << endl;
}

const Tile& Map::getCenterTile()
{
	return mapTiles_[0];
}

