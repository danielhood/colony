#pragma once

#include <iostream>
#include <vector>

#include "tile.h"

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
			return (int) mapTiles_.size();
		}

		Tile& getCenterTile();
		Tile& getTile(int x, int y);

	protected:
		static const int MaxRings = 100;
		
		static inline int ringSize(int ring) { 
			// Ring 0 is the center tile
			if (ring == 0) return 1;

			return 6 * ring; 
		}

		static inline int totalNodesForRing(int ring) { return 1 + 3 * ring * (ring + 1); }

		vector<shared_ptr<Tile>> mapTiles_ = {};

		int numTiles_ = 0;

		void generateTiles(int numRings);
		shared_ptr<Tile> generateTile(vector<shared_ptr<Tile>>& newTiles);
		void generateImmediateNeighbours(shared_ptr<Tile> t, vector<shared_ptr<Tile>>& newTiles);
};
