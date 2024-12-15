//
// Created by Strohmeier on 04/12/2024.
//

#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

namespace DataStructs
{
    struct Point3
    {
        int x, y, z;
        explicit Point3(const int tx, const int ty, const int tz) : x(tx), y(ty), z(tz) {}

        // operator== for unordered_map and hashing required
        bool operator==(const Point3& other) const
        {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    struct Velocity
    {
        int dir_x, dir_y, dir_z;
        explicit Velocity(const int tx, const int ty, const int tz) : dir_x(tx), dir_y(ty), dir_z(tz) {}
    };
}
#endif //DATASTRUCTS_H
