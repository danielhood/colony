#include <iostream>
#include "gtest/gtest.h"
#include "map/map.h"

namespace colony_test_map {

	class TestMap : public ::testing::Test {
		protected:
			TestMap() {}
			virtual ~TestMap() {}
			virtual void SetUp() {}
			virtual void TearDown() {}
	};


	TEST_F(TestMap, InitalMap_NumTiles_HasMaxTiles) {
		Map map = Map::getMap();
		EXPECT_EQ(Map::getMaxTiles(), map.numTiles());
	}	

	TEST_F(TestMap, InitalMap_CenterTile_HasSixLinks) {
		Map map = Map::getMap();
		EXPECT_EQ(6, map.getCenterTile().numLinks());
	}
	
	TEST_F(TestMap, InitalMap_CenterTileFirstLink_HasId1) {
		Map map = Map::getMap();
		Tile& tile = map.getCenterTile().getLink(0);
		EXPECT_EQ(1, tile.getId());
	}

	TEST_F(TestMap, InitalMap_CenterTileFirstLink_CanUpdateId) {
		Map map = Map::getMap();
		Tile& tile = map.getCenterTile().getLink(0);
		int origId = tile.getId();
		tile.setId(origId+1);
		EXPECT_EQ(origId+1, map.getCenterTile().getLink(0).getId());
	}

	TEST_F(TestMap, InitalMap_CenterTile_CanUpdateId) {
		Map map = Map::getMap();
		Tile& tile = map.getCenterTile();
		int origId = tile.getId();
		tile.setId(origId+1);
		EXPECT_EQ(origId+1, map.getCenterTile().getId());
	}
}
