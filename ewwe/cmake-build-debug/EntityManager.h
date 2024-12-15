//
// Created by Stroh on 04/12/2024.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <memory>
#include <vector>

#include "Entity.h"


class EntityManager
{
    public:
        EntityManager();

    private:
        std::vector<std::shared_ptr<Entity>> entities;
};



#endif //ENTITYMANAGER_H
