#pragma once

#include<string>
#include<unordered_map>

#include "Entity.h"
#include "Singletone.h"

class EntityManager : public Singleton<EntityManager>
{
public:
    void addEntityData(Entity&& entity);
    Entity* getEntityData(std::string name);
    Entity&& getEntity(std::string name);

private:
    std::unordered_map<std::string, Entity> _entityData;
};

