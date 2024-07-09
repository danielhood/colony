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
		Tile testTile = map.getTile(2,4);

		EXPECT_EQ(true, testTile.isAdjacentTo(2,6));
		EXPECT_EQ(true, testTile.isAdjacentTo(3,5));
		EXPECT_EQ(true, testTile.isAdjacentTo(3,3));
		EXPECT_EQ(true, testTile.isAdjacentTo(2,2));
		EXPECT_EQ(true, testTile.isAdjacentTo(1,3));
		EXPECT_EQ(true, testTile.isAdjacentTo(1,5));
	}	

	TEST_F(TestMap, InitalMap_CenterTileFirstLink_HasCoord_0_2) {
		Map map = Map::getMap();
		Tile& tile = map.getCenterTile().getLink(0);
		EXPECT_EQ(0, tile.getX());
		EXPECT_EQ(2, tile.getY());
	}

	TEST_F(TestMap, InitalMap_CenterTileAndFirstRingTile_ValidReverseLink) {
		Map map = Map::getMap();
		Tile& centerTile = map.getCenterTile();

		// Check that a back link exists to center tile on all first ring tiles
		for (int i = 0; i<6; ++i) {	
			bool linkFound = false;
			for (int j = 0; j<6; j++) {
				if (true == (linkFound = (&centerTile == &centerTile.getLink(i).getLink(j)))) break;
			}
			EXPECT_EQ(true, linkFound); 
		}
	}

	TEST_F(TestMap, InitialMap_TraverseBackToOriginalTile) {
		Map map = Map::getMap();
		Tile startTile = map.getTile(2, 4);

		// Traverse around 6 tiles back to start tile
		Tile endTile = startTile.getLink(0).getLink(1).getLink(2).getLink(3).getLink(4).getLink(5);

		EXPECT_EQ(2, endTile.getX());
		EXPECT_EQ(4, endTile.getY());
	}
}
