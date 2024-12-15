//
// Created by Strohmeier on 03/12/2024.
//
#pragma once

#include <memory>
#include <vector>
#include "Datastructs.h"
#include "Chunk.h"
#include <queue>

#ifndef WORLD_H
#define WORLD_H

// Hasher for ChunkCoords
struct ChunkCoords
{
    int x, y, z;

    bool operator==(const ChunkCoords& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct ChunkCoordsHasher
{
    size_t operator()(const ChunkCoords& coords) const
    {
        return std::hash<int>()(coords.x) ^ (std::hash<int>()(coords.y) << 1) ^ (std::hash<int>()(coords.z) << 2);
    }
};

namespace WORLD
{
    class World
    {
        public:
            World();

            [[nodiscard]] uint8_t getBlock(DataStructs::Point3 point) const;
            void setBlock(DataStructs::Point3 point, MapBlockType type);

            void updatePlayerPosition(DataStructs::Point3 player_pos);
            [[nodiscard]] ChunkCoords getPlayerPosition(int playerX, int playerY, int playerZ) const;
            void setPlayerPosition(int playerX, int playerY, int playerZ);

            void spreadGas(int x, int y, int z);
        private:
            std::unordered_map<ChunkCoords, std::shared_ptr<MAP_GRID::Chunk>, ChunkCoordsHasher> chunks;
            int chunkLoadRadius;

            std::vector<MapBlockInfo> unstable_blocks;
            std::vector<MapBlockInfo> gas_to_spread;

            void loadChunksAround(DataStructs::Point3 player_pos);
            void unloadFarChunks(DataStructs::Point3 player_pos);
    };
}


#endif // WORLD_H
