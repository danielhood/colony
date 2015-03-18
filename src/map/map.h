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
		static int getMaxTiles() { return totalNodesForRing(MaxRings); }

		int numTiles() {
			return mapTiles_.size();
		}

		Tile& getCenterTile();

	protected:
		static const int MaxRings = 7;
		
		static inline int ringSize(int ring) { return 6 * ring; }

		static inline int totalNodesForRing(int ring) { return 1 + 3 * ring * (ring + 1); }

		static inline bool isKeyNode(int ring, int pos) { return 0 == pos % ringSize(ring); }
		static inline bool isKeyNode(Tile& tile) { return isKeyNode(tile.getRing(), tile.getPos()); }

		inline auto getRingStart(Tile& tile) { return mapTiles_.begin() + totalNodesForRing(tile.getRing() - 1); }
		inline auto getRingEnd(Tile& tile) { return mapTiles_.begin() + totalNodesForRing(tile.getRing() - 1); }

		int numTiles_ = 0;

		void generateTiles();
		void linkFirstRing();
		void linkRings(Tile& startTile);

		vector<Tile> mapTiles_ = {};
};
