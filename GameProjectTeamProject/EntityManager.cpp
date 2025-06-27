#include "EntityManager.h"

void EntityManager::addEntityData(std::string name, Entity&& entity) {
    _entityData.insert({ name, std::move(entity) });
}

Entity* EntityManager::getEntityData(std::string name) {
    std::unordered_map<std::string, Entity>::iterator it = _entityData.find(name);

    if (it != _entityData.end())
        return &it->second;
    return nullptr;
}

Entity&& EntityManager::getEntity(std::string name) {
    std::unordered_map<std::string, Entity>::iterator it = _entityData.find(name);
    if (it == _entityData.end())
        throw "Have not key";
    Entity entity = it->second;
    return std::move(entity);
}
