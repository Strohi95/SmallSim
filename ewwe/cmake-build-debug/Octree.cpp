//
// Created by Strohmeier on 05/12/2024.
//

#include "Octree.h"


Octree::Octree(int x1, int y1, int z1, int x2, int y2, int z2)
{

}

MapBlockInfo* Octree::getMapBlockInfo()
{
    return mapBlockInfo;
}

DataStructs::Point3* Octree::getTopLeftCorner()
{
    return top_left_front_corner;
}
DataStructs::Point3 getBottomRightBackCorner();
DataStructs::Point3 getBlockCoordinates();
Octree* getParent();
std::vector<Octree*> getChildren();