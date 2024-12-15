#include "World.h"

#include <unordered_set>

using namespace WORLD;
using namespace std;

namespace WORLD
{
    World::World() : chunkLoadRadius(4) // Example load radius
    {
        loadChunksAround(DataStructs::Point3(0, 0, 0));
    }

    uint8_t World::getBlock(const DataStructs::Point3 point) const
    {
        auto chunk_Pos = DataStructs::Point3(
            point.x / MAP_GRID::Chunk::CHUNK_SIZE,
            point.y / MAP_GRID::Chunk::CHUNK_SIZE,
            point.z / MAP_GRID::Chunk::CHUNK_SIZE);

        auto local_Pos = DataStructs::Point3(
            point.x % MAP_GRID::Chunk::CHUNK_SIZE,
            point.y % MAP_GRID::Chunk::CHUNK_SIZE,
            point.z % MAP_GRID::Chunk::CHUNK_SIZE);

        // Handle negative coordinates
        if (local_Pos.x < 0) { local_Pos.x += MAP_GRID::Chunk::CHUNK_SIZE; chunk_Pos.x--; }
        if (local_Pos.y < 0) { local_Pos.y += MAP_GRID::Chunk::CHUNK_SIZE; chunk_Pos.y--; }
        if (local_Pos.z < 0) { local_Pos.z += MAP_GRID::Chunk::CHUNK_SIZE; chunk_Pos.z--; }

        const ChunkCoords coords = { chunk_Pos.x, chunk_Pos.y, chunk_Pos.z };

        if (const auto it = chunks.find(coords); it != chunks.end())
        {
            return it->second->getBlockType(local_Pos);
        }

        return static_cast<MapBlockType>(MapBlockType::AIR); // Default block type
    }

    void World::setBlock(const DataStructs::Point3 point, const MapBlockType type)
    {
        auto chunk_Pos = DataStructs::Point3(
            point.x / MAP_GRID::Chunk::CHUNK_SIZE,
            point.y / MAP_GRID::Chunk::CHUNK_SIZE,
            point.z / MAP_GRID::Chunk::CHUNK_SIZE);

        auto local_Pos = DataStructs::Point3(
            point.x % MAP_GRID::Chunk::CHUNK_SIZE,
            point.y % MAP_GRID::Chunk::CHUNK_SIZE,
            point.z % MAP_GRID::Chunk::CHUNK_SIZE);

        // Handle negative coordinates
        if (local_Pos.x < 0) { local_Pos.x += MAP_GRID::Chunk::CHUNK_SIZE; chunk_Pos.x--; }
        if (local_Pos.y < 0) { local_Pos.y += MAP_GRID::Chunk::CHUNK_SIZE; chunk_Pos.y--; }
        if (local_Pos.z < 0) { local_Pos.z += MAP_GRID::Chunk::CHUNK_SIZE; chunk_Pos.z--; }

        ChunkCoords coords = { chunk_Pos.x, chunk_Pos.y, chunk_Pos.z };

        if (const auto it = chunks.find(coords); it != chunks.end())
        {
            it->second->setBlockType(local_Pos, type);
        }
        else
        {
            // Optionally, create the chunk if it doesn't exist
            auto newChunk = std::make_shared<MAP_GRID::Chunk>(chunk_Pos.x, chunk_Pos.y, chunk_Pos.z);
            newChunk->setBlockType(local_Pos, type);
            chunks.emplace(coords, newChunk);
        }
    }

    void World::updatePlayerPosition(const DataStructs::Point3 player_pos)
    {
        auto local_Player_Pos = DataStructs::Point3(
         player_pos.x / MAP_GRID::Chunk::CHUNK_SIZE,
         player_pos.y / MAP_GRID::Chunk::CHUNK_SIZE,
         player_pos.z / MAP_GRID::Chunk::CHUNK_SIZE);

        // Handle negative coordinates if necessary

        loadChunksAround(player_pos);
        unloadFarChunks(player_pos);
    }

    void World::loadChunksAround(const DataStructs::Point3 player_pos)
    {
        for (int x = player_pos.x - chunkLoadRadius; x <= player_pos.x + chunkLoadRadius; x++)
        {
            for (int y = player_pos.y - chunkLoadRadius; y <= player_pos.y + chunkLoadRadius; y++)
            {
                for (int z = player_pos.z - chunkLoadRadius; z <= player_pos.z + chunkLoadRadius; z++)
                {
                    if (ChunkCoords coords = { x, y, z }; !chunks.contains(coords))
                    {
                        auto newChunk = std::make_shared<MAP_GRID::Chunk>(x, y, z);
                        chunks.emplace(coords, newChunk);
                    }
                }
            }
        }
    }

    void World::unloadFarChunks(const DataStructs::Point3 player_pos)
    {
        for (auto it = chunks.begin(); it != chunks.end(); )
        {
            int distance_X = it->first.x - player_pos.x;
            int distance_Y = it->first.y - player_pos.y;
            int distance_Z = it->first.z - player_pos.z;

            if (abs(distance_X) > chunkLoadRadius ||
                abs(distance_Y) > chunkLoadRadius ||
                abs(distance_Z) > chunkLoadRadius)
            {
                it = chunks.erase(it); // Unload chunk
            }
            else
            {
                ++it;
            }
        }
    }

    void World::spreadGas(int x, int y, int z)
    {
        queue<DataStructs::Point3> gasQueue;
        unordered_set<size_t> visited;

        // Start spreading from the source block
        gasQueue.emplace(x, y, z);
        setBlock(DataStructs::Point3(x, y, z), MapBlockType::GAS);

        // Simple hashing for visited tracking (could be optimized)
        constexpr Point3Hasher hasher;
        visited.insert(hasher(DataStructs::Point3(x, y, z)));

        while (!gasQueue.empty())
        {
            const DataStructs::Point3 current = gasQueue.front();
            gasQueue.pop();

            // Define adjacent directions
            std::vector<DataStructs::Point3> directions = {
                DataStructs::Point3(1, 0, 0),
                DataStructs::Point3(-1, 0, 0),
                DataStructs::Point3(0, 1, 0),
                DataStructs::Point3(0, -1, 0),
                DataStructs::Point3(0, 0, 1),
                DataStructs::Point3(0, 0, -1)
            };

            for (const auto& dir : directions)
            {
                DataStructs::Point3 neighbor(current.x + dir.x, current.y + dir.y, current.z + dir.z);

                size_t neighborHash = hasher(neighbor);
                if (visited.contains(neighborHash))
                    continue;

                // Check if the neighbor block is AIR
                if (const uint8_t neighborType = getBlock(neighbor); neighborType == MapBlockType::AIR)
                {
                    setBlock(neighbor, MapBlockType::GAS);
                    gasQueue.push(neighbor);
                    visited.insert(neighborHash);
                }
            }
        }
    }
}
