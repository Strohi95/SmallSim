//
// Created by Strohmeier on 04/12/2024.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <string>
#include <utility>

#include "Datastructs.h"


class Entity
{
    public:
        Entity(const int id, std::string description, const DataStructs::Point3 coordinates, const int hp, const int ad, const int hs) : entity_id(id), entity_description(std::move(description)),
               entity_coordinates(coordinates), entity_velocity(DataStructs::Velocity(0, 0, 0)), entity_health_points(hp), entity_attack_damage(ad), entity_health_strength(hs) { };
    private:
        int entity_id;
        std::string entity_description;
        DataStructs::Point3 entity_coordinates;
        DataStructs::Velocity entity_velocity;
        int entity_health_points;
        int entity_attack_damage;
        int entity_health_strength;
};



#endif //ENTITY_H
