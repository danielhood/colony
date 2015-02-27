#pragma once

#include <iostream>

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
		static Map getMap() {
			Map newMap = {};
			return newMap;	
		}

		int numTiles() {
			return numTiles_;
		}

	protected:
		int numTiles_ = 0;
};
