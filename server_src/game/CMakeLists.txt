target_sources(taller_game
    PRIVATE

    world.cpp
    ../editor_parser/editor_parser.cpp

    entities/mineral.cpp
    entities/merchant.cpp
    entities/rotating_merchant.cpp
    entities/merchants_factory.cpp
    entities/door.cpp
    entities/bed.cpp
    entities/player.cpp
    entities/crop.cpp
    entities/enemies/enemy.cpp
    entities/enemies/enemies_factory.cpp
    entities/enemies/trap.cpp
    entities/enemies/vampire.cpp
    entities/chest.cpp

    inventory/inventory.cpp
    inventory/inventory_slot.cpp
    inventory/mineral_item.cpp
    inventory/crop_item.cpp
    inventory/bed_item.cpp
    inventory/animal_item.cpp
    inventory/chest_item.cpp
    inventory/chicken_egg.cpp
    inventory/cow_milk.cpp
    inventory/decoration_item.cpp
    inventory/item_factory.cpp

    commands/move_command.cpp
    commands/join_command.cpp
    commands/leave_command.cpp
    commands/select_tool_command.cpp
    commands/mine_command.cpp
    commands/collect_command.cpp
    commands/spawn_animal_command.cpp
    commands/plant_command.cpp
    commands/water_command.cpp
    commands/attack_command.cpp
    commands/interact_command.cpp
    commands/till_command.cpp
    commands/gift_offer_command.cpp
    commands/gift_response_command.cpp
    commands/chat_command.cpp
    commands/chat/merchant_command.cpp
    commands/chat/buy_command.cpp
    commands/chat/sell_command.cpp
    commands/chat/catalog_command.cpp
    commands/chat/unknown_command.cpp
    commands/place_command.cpp
    commands/chest_move_command.cpp
    commands/redeem_set_command.cpp
    commands/cheats/amount_cheat_command.cpp
    commands/cheats/life_cheat_command.cpp
    commands/cheats/energy_cheat_command.cpp
    commands/cheats/gold_cheat_command.cpp

    commands/cheats/cheat_water_crop_command.cpp
    commands/cheats/cheat_growth_command.cpp
    commands/cheats/cheat_end_day_command.cpp
    commands/cheats/cheat_enemies_damage_command.cpp

    sectors/sector.cpp
    sectors/cavern_sector.cpp
    sectors/farm_sector.cpp
    sectors/village_sector.cpp

    sets/set_animal.cpp
    sets/set_crop.cpp
    sets/set_fight.cpp
    sets/set_gold.cpp
    sets/set_metal.cpp
)
