//
// Created by Strohmeier on 05/12/2024.
//
#pragma once

#include <cstdint>
#include <vector>

#include "Datastructs.h"
#include "Chunk.h"

#ifndef OCTREE_H
#define OCTREE_H


class Octree
{
    private:
        MapBlockInfo* mapBlockInfo {};

        DataStructs::Point3 *top_left_front_corner {}, *bottom_right_back_corner {};

        std::vector<Octree*> children;
        Octree* parent = {};
    public:
        Octree() = default;
        explicit Octree(MapBlockInfo* temp_mapBlockInfo) : mapBlockInfo(temp_mapBlockInfo) {};
        Octree(int x1, int y1, int z1, int x2, int y2, int z2);

    MapBlockInfo* getMapBlockInfo();
    DataStructs::Point3* getTopLeftCorner();
    DataStructs::Point3 getBottomRightBackCorner();
    DataStructs::Point3 getBlockCoordinates();
    Octree* getParent();
    std::vector<Octree*> getChildren();
};



#endif //OCTREE_H
