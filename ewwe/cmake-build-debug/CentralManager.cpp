#include <iostream>
#include "World.h"

int main()
{
    WORLD::World world;

    // Set a block at (10, 0, 10) to GRASS
    //world.setBlock(DataStructs::Point3(10, 0, 10), MapBlockType::GRASS);

    // Get the block type at (10, 0, 10)
    uint8_t blockType = world.getBlock(DataStructs::Point3(10, 0, 10));
    std::cout << "Block at (10, 0, 10) is of type: " << static_cast<MapBlockType>(blockType) << std::endl;

    // Get a block that hasn't been set explicitly (should be AIR)
    blockType = world.getBlock(DataStructs::Point3(15, 1, 15));
    std::cout << "Block at (15, 1, 15) is of type: " << static_cast<MapBlockType>(blockType) << std::endl;

    // Update player position to (10, 0, 10)
    //world.updatePlayerPosition(DataStructs::Point3(10, 0, 10));
    //world.setBlock(DataStructs::Point3(10, 0, 0), MapBlockType::GRASS);
    blockType = world.getBlock(DataStructs::Point3(-1, -1, -1));
    std::cout << "Block at (10, 0, 0) is of type: " << static_cast<MapBlockType>(blockType) << std::endl;

    return 0;
}

