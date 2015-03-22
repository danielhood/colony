#include "gtest/gtest.h"
#include "map/tile.h"

namespace colony_test_tile {
	class TestTile : public ::testing::Test {
		protected:
			TestTile() {}
			virtual ~TestTile() {}
			virtual void SetUp() {}
			virtual void TearDown() {}
	};

	TEST_F(TestTile, Tile_CoordinateSet_CannotUpdateCoord) {
		Tile tile = {};
	
		tile.setCoord(0,0);

		ASSERT_ANY_THROW(tile.setCoord(9, 100));
	}
	
	TEST_F(TestTile, Tile_SixLinksSet_CannotAddNewLink) {
		Tile tile = {};
		Tile tile2 = {};

		for (int i=0; i<6; ++i) {
			tile.addLink(tile2);
		}

		ASSERT_ANY_THROW(tile.addLink(tile));
	}



}
