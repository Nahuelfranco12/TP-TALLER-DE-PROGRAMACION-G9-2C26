#include "gtest/gtest.h"

#include "server_src/game/entities/player.h"
#include "server_src/game/sectors/cavern_sector.h"

namespace {

TEST(CavernSectorTest, InitializesWithinConfiguredMineralBounds)
{
    CavernLevelConfig config{1, 1, 0, 0, {MineralTypes::COAL}};
    CavernSector cavern(5, 5, IdSector::CAVERN_LEVEL_1, config);

    SectorState state = cavern.state();
    ASSERT_EQ(state.entities.size(), 1);
    EXPECT_EQ(state.entities.front().type, EntityTypes::MINERAL);
    EXPECT_EQ(state.entities.front().mineral.type, MineralTypes::COAL);
}

TEST(CavernSectorTest, ResetsMineralsWhenTheLastPlayerLeaves)
{
    CavernLevelConfig config{1, 1, 0, 0, {MineralTypes::IRON}};
    CavernSector cavern(5, 5, IdSector::CAVERN_LEVEL_1, config);
    PlayerOutfit outfit(PlayerHats::HAT_DEFAULT, PlayerHairs::BLONDE,
                        PlayerShirts::TSHIRT_DEFAULT, PlayerPants::PANTS_DEFAULT);

    ASSERT_TRUE(cavern.addEntity(std::make_unique<Player>(0, 0, 1, &cavern,
                                                          outfit),
                                                          Position(0, 0)));
    EXPECT_EQ(cavern.playerCount(), 1);
    cavern.removeEntity(Position(0, 0));
    cavern.endDay();

    SectorState state = cavern.state();
    ASSERT_EQ(state.entities.size(), 1);
    EXPECT_EQ(state.entities.front().type, EntityTypes::MINERAL);
}

} // namespace