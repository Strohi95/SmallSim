//
// Created by Stroh on 05/12/2024.
//

#include "Chunk.h"

namespace MAP_GRID
{
    Chunk::Chunk(const int chunkX, const int chunkY, const int chunkZ) : chunkX(chunkX), chunkY(chunkY), chunkZ(chunkZ)
    {
        /* Initialize ground layer blocks
        for (int localX = 0; localX < CHUNK_SIZE; localX++)
        {
            for (int localY = 0; localY < CHUNK_SIZE; localY++)
            {
                // z=0 is the ground layer
                DataStructs::Point3 localPos(localX, localY, 0);
                chunk_blocks.emplace(localPos, MapBlockInfo(MapBlockType::DIRT, localPos));
            }
        }*/
    }

    uint8_t Chunk::getBlockType(const DataStructs::Point3 local_point) const
    {
        const DataStructs::Point3 localPos(local_point.x, local_point.y, local_point.z);

        if (const auto it = chunk_blocks.find(localPos); it != chunk_blocks.end())
        {
            return it->second.block_type;
        }

        return static_cast<uint8_t>(MapBlockType::AIR); // Default block type
    }

    void Chunk::setBlockType(const DataStructs::Point3 local_point, const MapBlockType type)
    {
        const DataStructs::Point3 localPos(local_point.x, local_point.y, local_point.z);

        if (type == MapBlockType::AIR)
        {
            chunk_blocks.erase(localPos); // Remove air blocks to save memory
        }
        else
        {
            chunk_blocks.emplace(localPos, MapBlockInfo(type, localPos));
        }
    }
}