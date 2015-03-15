#pragma once

#include <iostream>
#include <vector>

#include "map/tile.h"

using namespace std;

class Map {
	protected:
		Map(){}

	public:
		Map(Map&&) =default;
    Map& operator=(Map&&) =default;

		Map(Map&) =delete;
		Map& operator=(const Map&) =delete;

		virtual ~Map(){}	
		
	public:
		static Map getMap();
		static constexpr int getMaxTiles() {
			return MaxTiles;
		}

		int numTiles() {
			return mapTiles_.size();
		}

		Tile& getCenterTile();



	protected:
		static const int MaxTiles = 7;
		
		int numTiles_ = 0;

		void generateTiles();
		void linkFirstRing();
		void linkRings(Tile& startTile);

		vector<Tile> mapTiles_ = {};
};
