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


	TEST_F(TestMap, InitalMap_HasZeroTiles) {
		Map map = Map::getMap();
		EXPECT_EQ(0, map.numTiles());
	}	

}
