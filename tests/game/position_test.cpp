#include "gtest/gtest.h"

#include "server_src/game/position.h"

TEST(PositionTest, ComparesCoordinates)
{
	Position first(2, 3);
	Position same(2, 3);
	Position different(3, 2);

	EXPECT_EQ(first, same);
	EXPECT_NE(first, different);
	EXPECT_TRUE(first < different);
}

TEST(PositionTest, DetectsOrthogonalAdjacency)
{
	Position center(4, 4);

	EXPECT_TRUE(center.isAdjacentTo(Position(4, 3)));
	EXPECT_TRUE(center.isAdjacentTo(Position(4, 5)));
	EXPECT_TRUE(center.isAdjacentTo(Position(3, 4)));
	EXPECT_TRUE(center.isAdjacentTo(Position(5, 4)));
}

TEST(PositionTest, RejectsDiagonalAndDistantPositions)
{
	Position center(4, 4);

	EXPECT_FALSE(center.isAdjacentTo(Position(3, 3)));
	EXPECT_FALSE(center.isAdjacentTo(Position(4, 4)));
	EXPECT_FALSE(center.isAdjacentTo(Position(6, 4)));
}