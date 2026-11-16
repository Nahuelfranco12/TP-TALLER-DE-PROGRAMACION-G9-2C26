target_sources(taller_game
    PRIVATE

    world.cpp

    entities/mineral.cpp
    entities/door.cpp
    entities/player.cpp
    entities/crop.cpp
    entities/enemy.cpp
    entities/enemies_factory.cpp
    entities/vampire.cpp

    inventory/inventory.cpp
    inventory/inventory_slot.cpp
    inventory/mineral_item.cpp
    inventory/crop_item.cpp
    inventory/chicken_egg.cpp
    inventory/cow_milk.cpp

    commands/move_command.cpp
    commands/join_command.cpp
    commands/leave_command.cpp
    commands/select_tool_command.cpp
    commands/mine_command.cpp
    commands/collect_command.cpp
    commands/spawn_mineral_command.cpp
    commands/spawn_animal_command.cpp
    commands/plant_command.cpp
    commands/water_command.cpp
    commands/attack_command.cpp
    commands/till_command.cpp
    commands/gift_offer_command.cpp
    commands/gift_response_command.cpp
    commands/chat_command.cpp

    commands/cheats/cheat_water_crop_command.cpp
    commands/cheats/cheat_growth_command.cpp

    sectors/sector.cpp
    sectors/cavern_sector.cpp
)