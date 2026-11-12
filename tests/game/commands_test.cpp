#include "gtest/gtest.h"

#include "common_src/game_dtos.h"
#include "server_src/game/commands/collect_command.h"
#include "server_src/game/commands/gift_offer_command.h"
#include "server_src/game/commands/gift_response_command.h"
#include "server_src/game/commands/join_command.h"
#include "server_src/game/commands/leave_command.h"
#include "server_src/game/commands/mine_command.h"
#include "server_src/game/commands/move_command.h"
#include "server_src/game/commands/plant_command.h"
#include "server_src/game/commands/select_tool_command.h"
#include "server_src/game/commands/spawn_animal_command.h"
#include "server_src/game/commands/spawn_mineral_command.h"
#include "server_src/game/commands/till_command.h"
#include "server_src/game/commands/water_command.h"
#include "server_src/game/world.h"

namespace {

PlayerOutfit outfit()
{
    return PlayerOutfit(PlayerHats::HAT_DEFAULT, PlayerHairs::BLONDE,
                        PlayerShirts::TSHIRT_DEFAULT, PlayerPants::PANTS_DEFAULT);
}

World makeWorld()
{
    World world(DaySpeed::SLOW);
    world.addSector(std::make_unique<Sector>(
        6, 6, IdSector::FARM, Terrain(true, true, TerrainType::DIRT)));
    world.addPlayer(1, outfit(), IdSector::FARM);
    return world;
}

TEST(CommandTest, SelectsToolsAndMovesPlayer)
{
    World world = makeWorld();
    Player *player = world.getPlayer(1);
    ASSERT_NE(player, nullptr);

    SelectToolCommand select(1, AvailableTools::SHOVEL);
    select.execute(world);
    EXPECT_EQ(player->getSelectedTool()->toolType, AvailableTools::SHOVEL);

    MoveCommand move(1, DirectionDto::Right);
    move.execute(world);
    EXPECT_EQ(player->position, Position(1, 0));
}

TEST(CommandTest, TillsAndPlantsAdjacentTile)
{
    World world = makeWorld();
    SelectToolCommand select(1, AvailableTools::SHOVEL);
    select.execute(world);
    TillCommand till(1, DirectionDto::Down);
    till.execute(world);
    EXPECT_TRUE(world.getSector(IdSector::FARM)->isTilled(Position(0, 1)));

    PlantCommand plant(1, Position(0, 1), CropTypes::STRAWBERRY);
    plant.execute(world);
    EXPECT_EQ(world.getSector(IdSector::FARM)->getEntity(Position(0, 1))->getType(),
              EntityTypes::CROP);
}

TEST(CommandTest, SpawnsAndMinesMineral)
{
    World world = makeWorld();
    SpawnMineralCommand spawn( IdSector::FARM, Position(1, 0), MineralTypes::COAL,
                                SPAWN_FREQ_COAL, PICKAXE_COUNT_COAL);
    spawn.execute(world);
    ASSERT_NE(world.getSector(IdSector::FARM)->getEntity(Position(1, 0)), nullptr);

    MineCommand mine(1, DirectionDto::Right);
    for (size_t hit = 0; hit < PICKAXE_COUNT_COAL; ++hit)
        mine.execute(world);
    EXPECT_EQ(world.getSector(IdSector::FARM)->getEntity(Position(1, 0)), nullptr);
}

TEST(CommandTest, SpawnsAnimals)
{
    World world = makeWorld();
    SpawnAnimalCommand spawn( IdSector::FARM, Position(2, 2), AnimalType::COW);
    spawn.execute(world);

    Entity *entity = world.getSector(IdSector::FARM)->getEntity(Position(2, 2));
    ASSERT_NE(entity, nullptr);
    EXPECT_EQ(entity->getType(), EntityTypes::ANIMAL);
}

TEST(CommandTest, JoinsAndLeavesTheWorld)
{
    World world(DaySpeed::SLOW);
    world.addSector(std::make_unique<Sector>(
        4, 4, IdSector::FARM, Terrain(true, true, TerrainType::DIRT)));

    JoinCommand join(8, outfit());
    join.execute(world);
    EXPECT_NE(world.getPlayer(8), nullptr);

    LeaveCommand leave(8);
    leave.execute(world);
    EXPECT_EQ(world.getPlayer(8), nullptr);
}

TEST(CommandTest, OffersAndAcceptsAnAdjacentGift)
{
    World world = makeWorld();
    world.addPlayer(2, outfit(), IdSector::FARM);
    Player *receiver = world.getPlayer(2);
    ASSERT_NE(receiver, nullptr);
    ASSERT_EQ(receiver->position, Position(0, 1));

    GiftOfferCommand offer(1, 2, 0);
    offer.execute(world);
    ASSERT_TRUE(receiver->hasPendingGift());
    EXPECT_EQ(receiver->getPendingGift().giverId, 1);

    size_t giverItems = world.getPlayer(1)->getInventory().state().items.size();
    GiftResponseCommand response(2, true);
    response.execute(world);

    EXPECT_FALSE(receiver->hasPendingGift());
    EXPECT_EQ(world.getPlayer(1)->getInventory().state().items.size(), giverItems - 1);
}

} // namespace