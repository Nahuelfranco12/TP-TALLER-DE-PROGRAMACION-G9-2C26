#include "gtest/gtest.h"

#include "server_src/game/game_constants.h"
#include "server_src/game/inventory/inventory.h"
#include "server_src/game/inventory/mineral_item.h"
#include "server_src/game/inventory/seed.h"

namespace {

class NonStackingItem : public Item {
public:
    explicit NonStackingItem(int subtype)
        : Item(1, ItemType::DECORATION_PRODUCT,
               static_cast<MineralTypes>(subtype)) {}

    bool stacksWith(const Item &) const override { return false; }
};

TEST(InventoryTest, StacksCompatibleItems)
{
    Inventory inventory;

    EXPECT_TRUE(inventory.addItem(std::make_unique<MineralItem>(PRICE_COAL,
                                                                 MineralTypes::COAL)));
    EXPECT_TRUE(inventory.addItem(std::make_unique<MineralItem>(PRICE_COAL,
                                                                 MineralTypes::COAL)));

    InventoryState state = inventory.state();
    ASSERT_EQ(state.items.size(), 1);
    EXPECT_EQ(state.items.front().count, 2);
}

TEST(InventoryTest, RejectsDuplicateTools)
{
    Inventory inventory;

    EXPECT_TRUE(inventory.addTool(std::make_unique<Tool>(AvailableTools::PICKAXE)));
    EXPECT_FALSE(inventory.addTool(std::make_unique<Tool>(AvailableTools::PICKAXE)));
    EXPECT_NE(inventory.getTool(AvailableTools::PICKAXE), nullptr);
    EXPECT_EQ(inventory.getTool(AvailableTools::SHOVEL), nullptr);
}

TEST(InventoryTest, EnforcesItemSlotLimit)
{
    Inventory inventory;
    for (int index = 0; index < MAX_INVENTORY_ITEMS; ++index)
        ASSERT_TRUE(inventory.addItem(std::make_unique<NonStackingItem>(index)));

    EXPECT_FALSE(inventory.addItem(std::make_unique<NonStackingItem>(99)));
    EXPECT_EQ(inventory.state().items.size(), MAX_INVENTORY_ITEMS);
}

TEST(InventoryTest, GivesAnExistingSlotToAnotherInventory)
{
    Inventory giver;
    Inventory receiver;
    ASSERT_TRUE(giver.addItem(std::make_unique<Seed>(10, CropTypes::POTATO)));

    EXPECT_TRUE(giver.giveSlotTo(0, receiver));
    EXPECT_FALSE(giver.giveSlotTo(0, receiver));
    EXPECT_TRUE(giver.state().items.empty());
    ASSERT_EQ(receiver.state().items.size(), 1);
    EXPECT_EQ(receiver.state().items.front().subtype,
              static_cast<int>(CropTypes::POTATO));
}

TEST(InventoryTest, StackFilledMaxCapacity)
{
    Inventory inventory;
    
    for (size_t i = 0; i < MAX_INVETORY_STACK; i++)
        EXPECT_TRUE(inventory.addItem(std::make_unique<MineralItem>(PRICE_COAL,
                                                            MineralTypes::COAL)));
    InventoryState state = inventory.state();
    ASSERT_EQ(state.items.size(), 1);
    EXPECT_EQ(state.items.front().count, MAX_INVETORY_STACK);
}

TEST(InventoryTest, StackTryFillMoreThanMaxCapacity)
{
    Inventory inventory;

    for (size_t i = 0; i < MAX_INVETORY_STACK; i++)
        ASSERT_TRUE(inventory.addItem(
            std::make_unique<MineralItem>(PRICE_COAL, MineralTypes::COAL)));

    ASSERT_TRUE(inventory.addItem(
        std::make_unique<MineralItem>(PRICE_COAL, MineralTypes::COAL)));

    InventoryState state = inventory.state();

    ASSERT_EQ(state.items.size(), 2);
    EXPECT_EQ(state.items[0].count, MAX_INVETORY_STACK);
    EXPECT_EQ(state.items[1].count, 1);
}

} // namespace