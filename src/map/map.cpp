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

	mapTiles_[0].addLink(mapTiles_[1]);
	mapTiles_[0].addLink(mapTiles_[2]);
	mapTiles_[0].addLink(mapTiles_[3]);
	mapTiles_[0].addLink(mapTiles_[4]);
	mapTiles_[0].addLink(mapTiles_[5]);
	mapTiles_[0].addLink(mapTiles_[6]);

	mapTiles_[0].getLink(0).setId(1);
}

Tile& Map::getCenterTile()
{
	return mapTiles_[0];
}

