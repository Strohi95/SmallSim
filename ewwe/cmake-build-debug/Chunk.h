//
// Created by Stroh on 05/12/2024.
//

#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Datastructs.h"
#include "Entity.h"

#ifndef CHUNK_H
#define CHUNK_H

enum MapBlockType
{
    DIRT = 101,
    GRASS = 102,
    WATER = 103,
    SAND = 104,
    SNOW = 105,
    LAVA = 106,
    WOOD = 107,
    STONE = 108,
    FLOOR = 109,
    WALL = 110,
    WATER_FLOW = 111,
    ROCK = 112,
    GAS = 113,
    ENTITY = 114,
    AIR = 120
};

struct Point3Hasher
{
    size_t operator()(const DataStructs::Point3& point) const
    {
        return std::hash<int>()(point.x) ^ (std::hash<int>()(point.y) << 1) ^ (std::hash<int>()(point.z) << 2);
    }
};

struct MapBlockInfo
{
    uint8_t block_type;
    DataStructs::Velocity block_velocity = DataStructs::Velocity(0, 0, 0);
    DataStructs::Point3 block_coordinates;

    explicit MapBlockInfo(const MapBlockType bt, const DataStructs::Point3 point) : block_type(static_cast<uint8_t>(bt)), block_coordinates(point) {}

    [[nodiscard]] int getBlockType() const { return static_cast<uint8_t>(block_type); }
};

namespace MAP_GRID
{
    class Chunk
    {
        public:
            static constexpr int CHUNK_SIZE = 32;

            Chunk(int chunkX, int chunkY, int chunkZ);

            [[nodiscard]] uint8_t getBlockType(DataStructs::Point3 local_point) const;
            void setBlockType(DataStructs::Point3 local_point, MapBlockType type);

        private:
            int chunkX, chunkY, chunkZ;
            DataStructs::Point3 *top_left_front_corner {}, *bottom_right_back_corner {};
            std::vector<Entity*> entities_in_chunk {};
            std::unordered_map<DataStructs::Point3, MapBlockInfo, Point3Hasher> chunk_blocks;
    };
}


#endif //CHUNK_H
