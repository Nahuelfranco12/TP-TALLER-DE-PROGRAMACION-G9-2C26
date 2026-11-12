#include "gtest/gtest.h"

#include "server_src/game/entities/crop.h"
#include "server_src/game/entities/mineral.h"
#include "server_src/game/entities/player.h"
#include "server_src/game/sectors/sector.h"
#include "server_src/game/world.h"

namespace {

PlayerOutfit outfit()
{
    return PlayerOutfit(PlayerHats::HAT_DEFAULT, PlayerHairs::BLONDE,
                        PlayerShirts::TSHIRT_DEFAULT, PlayerPants::PANTS_DEFAULT);
}

TEST(MineralTest, DepletesAfterConfiguredHits)
{
    Mineral mineral(1, 1, MineralTypes::IRON, SPAWN_FREQ_IRON,
                     PICKAXE_COUNT_IRON);

    for (size_t hit = 0; hit + 1 < PICKAXE_COUNT_IRON; ++hit)
        EXPECT_FALSE(mineral.hit());
    EXPECT_TRUE(mineral.hit());
    EXPECT_EQ(mineral.getHitsLeft(), 0);
}

TEST(CropTest, StartsNeedingWaterAndCanBeWatered)
{
    Crop crop(Position(1, 1), CropTypes::STRAWBERRY);

    EXPECT_TRUE(crop.needsWater());
    EXPECT_TRUE(crop.water());
    EXPECT_FALSE(crop.needsWater());
    EXPECT_FALSE(crop.water());
}

TEST(PlayerTest, StartsWithToolsAndCanSpendEnergy)
{
    Sector sector(4, 4, IdSector::FARM, Terrain(true, true, TerrainType::DIRT));
    Player player(0, 0, 7, &sector, outfit());

    EXPECT_NE(player.getInventory().getTool(AvailableTools::PICKAXE), nullptr);
    EXPECT_EQ(player.getEnergy(), PLAYER_MAX_ENERGY);
    EXPECT_TRUE(player.spendEnergy(ENERGY_COST_MINE));
    EXPECT_EQ(player.getEnergy(), PLAYER_MAX_ENERGY - ENERGY_COST_MINE);
    player.restoreEnergy(ENERGY_COST_MINE);
    EXPECT_EQ(player.getEnergy(), PLAYER_MAX_ENERGY);
}

TEST(WorldTest, ManagesSectorsPlayersAndSpawns)
{
    World world(DaySpeed::SLOW);
    ASSERT_TRUE(world.addSector(std::make_unique<Sector>(
        5, 5, IdSector::FARM, Terrain(true, true, TerrainType::DIRT))));
    EXPECT_FALSE(world.addSector(std::make_unique<Sector>(
        5, 5, IdSector::FARM, Terrain(true, true, TerrainType::DIRT))));

    world.addPlayer(7, outfit(), IdSector::FARM);
    ASSERT_NE(world.getPlayer(7), nullptr);
    EXPECT_EQ(world.getSector(IdSector::FARM)->playerCount(), 1);
    EXPECT_TRUE(world.spawnMineral(IdSector::FARM, Position(2, 2),
                                   MineralTypes::COAL, SPAWN_FREQ_COAL,
                                   PICKAXE_COUNT_COAL));
    EXPECT_TRUE(world.spawnAnimal(IdSector::FARM, Position(3, 3),
                                  AnimalType::CHICKEN));
    EXPECT_FALSE(world.spawnAnimal(IdSector::VILLAGE, Position(0, 0),
                                   AnimalType::CHICKEN));

    world.removePlayer(7);
    EXPECT_EQ(world.getPlayer(7), nullptr);
}

} // namespace