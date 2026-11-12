#include "gtest/gtest.h"

#include "server_src/game/entities/entity.h"
#include "server_src/game/sectors/sector.h"

namespace {

class TestEntity : public Entity {
public:
    TestEntity(size_t x, size_t y) : Entity(x, y, EntityTypes::NPC) {}
};

TEST(SectorTest, AddsAndRemovesEntities)
{
    Sector sector(4, 4, IdSector::FARM, Terrain(true, true, TerrainType::DIRT));
    Position position(1, 2);

    EXPECT_TRUE(sector.addEntity(std::make_unique<TestEntity>(0, 0), position));
    EXPECT_FALSE(sector.addEntity(std::make_unique<TestEntity>(0, 0), position));
    ASSERT_NE(sector.getEntity(position), nullptr);
    EXPECT_EQ(sector.getEntity(position)->position, position);

    EXPECT_NE(sector.removeEntity(position), nullptr);
    EXPECT_EQ(sector.getEntity(position), nullptr);
}

TEST(SectorTest, MovesOnlyToValidEmptyPositions)
{
    Sector sector(4, 4, IdSector::FARM, Terrain(true, false, TerrainType::GRASS));
    Position origin(1, 1);
    Position destination(1, 2);
    ASSERT_TRUE(sector.addEntity(std::make_unique<TestEntity>(0, 0), origin));

    MoveResult result = sector.move(origin, destination);

    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.position, destination);
    EXPECT_EQ(sector.getEntity(origin), nullptr);
    EXPECT_NE(sector.getEntity(destination), nullptr);
    EXPECT_FALSE(sector.move(destination, Position(8, 8)).success);
}

TEST(SectorTest, TillsArableTilesOnce)
{
    Sector sector(3, 3, IdSector::FARM, Terrain(true, true, TerrainType::DIRT));
    Position position(1, 1);

    EXPECT_TRUE(sector.till(position));
    EXPECT_TRUE(sector.isTilled(position));
    EXPECT_FALSE(sector.till(position));
    EXPECT_FALSE(sector.till(Position(9, 9)));
}

} // namespace