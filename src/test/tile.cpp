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
	
		tile.setCoords(0,0);

		ASSERT_ANY_THROW(tile.setCoords(9, 100));
	}
}
