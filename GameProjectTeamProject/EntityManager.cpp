#include "EntityManager.h"

#include "Core.h"

EntityManager::EntityManager() {
    Core::GetInstance()->AddUpdate(this);
}

EntityManager::~EntityManager() {
    Core::GetInstance()->RemoveUpdate(this);

    // for문 돌리면 handleDeadEvent때문에 _activeEntities의 iterator가 바뀜
    std::vector<Object*> tempData = _activeObjects;

    for (Object* activeObject : tempData)
        deleteObject(activeObject);

    for (auto& entityDataPool : _objectDataPoolMap)
        for (auto& entityData : entityDataPool.second)
            delete entityData.second;

    _objectDataPoolMap.clear();
}

void EntityManager::addObjectData(std::string dataPool, std::string name, Object*&& entity) {
    std::unordered_map<std::string, Object*>& dataMap = _objectDataPoolMap[dataPool];
    dataMap.insert({ name , std::move(entity) });
}

Object* EntityManager::getObjectData(std::string dataPool, std::string name) {
    std::unordered_map<std::string, std::unordered_map<std::string, Object*>>::iterator it = _objectDataPoolMap.find(dataPool);

    if (it != _objectDataPoolMap.end()) {
        std::unordered_map<std::string, Object*>::iterator dataIt = it->second.find(name);
        if (dataIt != it->second.end())
            return dataIt->second;

    }
    return nullptr;
}

Object* EntityManager::activeObject(std::string dataPool, std::string name) {
    Object* targetEntity = getObjectData(dataPool, name);

    if (targetEntity == nullptr)
        return nullptr;

    Object* objectPtr = targetEntity->newClone();
    // 활성화
    objectPtr->active();

    Entity* entityPtr = dynamic_cast<Entity*>(objectPtr);
    if (entityPtr != nullptr) {
        // 사망 후 delete를 위한 구독
        entityPtr->addDeadListener(this);
    }
    _activeObjects.push_back(objectPtr);

    return objectPtr;
}

Object* EntityManager::activeRandomObject(std::string dataPool) {
    std::unordered_map<std::string, std::unordered_map<std::string, Object*>>::iterator it = _objectDataPoolMap.find(dataPool);

    if (it != _objectDataPoolMap.end()) {
        std::unordered_map<std::string, Object*>::iterator dataIt = it->second.begin();
        int randIndex = rand() % it->second.size();
        // randIndex만큼 iterator 이동
        std::advance(dataIt, randIndex);
        return activeObject(dataPool, dataIt->first);
    }

    return nullptr;
}

void EntityManager::handleDeadEvent(Entity* deadEntity) {
    if (deadEntity == nullptr)
        return;

    bool contains = std::find(_activeObjects.begin(), _activeObjects.end(), deadEntity) != _activeObjects.end();
    if (!contains)
        return;

    _toDeletedEntityQueue.push(deadEntity);
}

void EntityManager::deleteObject(Object* deadEntity) {
    if (deadEntity == nullptr)
        return;

    // 비활성화 (참조 시킨 포인터 제거)
    deadEntity->deActive();
    _activeObjects.erase(std::remove(_activeObjects.begin(), _activeObjects.end(), deadEntity), _activeObjects.end());
    // 삭제
    delete deadEntity;
}

void EntityManager::deleteAllActiveObject() {
    std::vector<Object*> tempData = _activeObjects;

    for (Object* activeObject : tempData)
        deleteObject(activeObject);
}

void EntityManager::Update() {
    while (!_toDeletedEntityQueue.empty()) {
        deleteObject(_toDeletedEntityQueue.front());
        _toDeletedEntityQueue.pop();
    }
}

int EntityManager::GetUpdatePriotity() {
    // 항상 처음에 실행 시켜야함
    return 2147483647;
}