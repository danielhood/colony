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

	TEST_F(TestMap, InitialMap_SingleTile_HasCorrectLinks) {
		Map map = Map::getMap();
		Tile testTile = map.getTile(4, 0);

		EXPECT_EQ(6, testTile.numLinks());

		EXPECT_EQ(true, testTile.isAdjacentTo(5,0));
		EXPECT_EQ(true, testTile.isAdjacentTo(5,1));
		EXPECT_EQ(true, testTile.isAdjacentTo(5,29));
		EXPECT_EQ(true, testTile.isAdjacentTo(4,1));
		EXPECT_EQ(true, testTile.isAdjacentTo(4,23));
		EXPECT_EQ(true, testTile.isAdjacentTo(3,0));
	}	

	TEST_F(TestMap, InitalMap_CenterTile_HasSixLinks) {
		Map map = Map::getMap();
		EXPECT_EQ(6, map.getCenterTile().numLinks());
	}
	
	TEST_F(TestMap, InitalMap_CenterTileFirstLink_HasCoord_1_0) {
		Map map = Map::getMap();
		Tile& tile = map.getCenterTile().getLink(0);
		EXPECT_EQ(1, tile.getRing());
		EXPECT_EQ(0, tile.getPos());
	}

	TEST_F(TestMap, InitalMap_CenterTileAndFirstRingTile_ValidReverseLink) {
		Map map = Map::getMap();
		Tile& centerTile = map.getCenterTile();

		// Check that a back link exists to cetner tile on all first ring tiles
		for (int i = 0; i<6; ++i) {	
			bool linkFound = false;
			for (int j = 0; j<centerTile.getLink(i).numLinks(); j++) {
				if (true == (linkFound = (&centerTile == &centerTile.getLink(i).getLink(j)))) break;
			}
			EXPECT_EQ(true, linkFound); 
		}
	}
}
