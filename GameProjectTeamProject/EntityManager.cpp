#include "EntityManager.h"

#include "Core.h"

EntityManager::EntityManager() {
    Core::GetInstance()->AddUpdate(this);
}

EntityManager::~EntityManager() {
    Core::GetInstance()->RemoveUpdate(this);

    // for문 돌리면 handleDeadEvent때문에 _activeEntities의 iterator가 바뀜
    std::vector<Entity*> tempData = _activeEntities;

    for (Entity* activeEntity : tempData)
        deleteEntity(activeEntity);

    for (auto& entityDataPool : _entityDataPoolMap)
        for (auto& entityData : entityDataPool.second)
            delete entityData.second;

    _entityDataPoolMap.clear();
}

void EntityManager::addEntityData(std::string dataPool, std::string name, Entity*&& entity) {
    std::unordered_map<std::string, Entity*>& dataMap = _entityDataPoolMap[dataPool];
    dataMap.insert({ name , std::move(entity) });
}

Entity* EntityManager::getEntityData(std::string dataPool, std::string name) {
    std::unordered_map<std::string, std::unordered_map<std::string, Entity*>>::iterator it = _entityDataPoolMap.find(dataPool);

    if (it != _entityDataPoolMap.end()) {
        std::unordered_map<std::string, Entity*>::iterator dataIt = it->second.find(name);
        if (dataIt != it->second.end())
            return dataIt->second;

    }
    return nullptr;
}

Entity* EntityManager::activeEntity(std::string dataPool, std::string name) {
    Entity* targetEntity = getEntityData(dataPool, name);

    if (targetEntity == nullptr)
        return nullptr;

    Entity* entityPtr = targetEntity->newClone();
    // 활성화
    entityPtr->active();
    // 사망 후 delete를 위한 구독
    entityPtr->addDeadListener(this);
    _activeEntities.push_back(entityPtr);

    return entityPtr;
}

Entity* EntityManager::activeRandomEntity(std::string dataPool) {
    std::unordered_map<std::string, std::unordered_map<std::string, Entity*>>::iterator it = _entityDataPoolMap.find(dataPool);

    if (it != _entityDataPoolMap.end()) {
        std::unordered_map<std::string, Entity*>::iterator dataIt = it->second.begin();
        int randIndex = rand() % it->second.size();
        // randIndex만큼 iterator 이동
        std::advance(dataIt, randIndex);
        return activeEntity(dataPool, dataIt->first);
    }

    return nullptr;
}

void EntityManager::handleDeadEvent(Entity* deadEntity) {
    if (deadEntity == nullptr)
        return;

    bool contains = std::find(_activeEntities.begin(), _activeEntities.end(), deadEntity) != _activeEntities.end();
    if (!contains)
        return;

    _toDeletedEntityQueue.push(deadEntity);
}

void EntityManager::deleteEntity(Entity* deadEntity) {
    if (deadEntity == nullptr)
        return;

    // 비활성화 (참조 시킨 포인터 제거)
    deadEntity->deActive();
    _activeEntities.erase(std::remove(_activeEntities.begin(), _activeEntities.end(), deadEntity), _activeEntities.end());
    // 삭제
    delete deadEntity;
}

void EntityManager::deleteAllActiveEnemy() {
    std::vector<Entity*> tempData = _activeEntities;

    for (Entity* activeEntity : tempData)
        deleteEntity(activeEntity);
}

void EntityManager::Update() {
    while (!_toDeletedEntityQueue.empty()) {
        deleteEntity(_toDeletedEntityQueue.front());
        _toDeletedEntityQueue.pop();
    }
}

int EntityManager::GetUpdatePriotity() {
    // 항상 처음에 실행 시켜야함
    return 2147483647;
}