#pragma once

#include<string>
#include<vector>
#include<unordered_map>
#include<queue>

#include "Entity.h"
#include "Singletone.h"
#include "IUpdate.h"

class EntityManager : public Singleton<EntityManager>, public IDeadHandler, public IUpdate
{
public:
    EntityManager();
    ~EntityManager() override;

public:
    void addObjectData(std::string dataPool, std::string name, Object*&& entity);
    Object* getObjectData(std::string dataPool, std::string name);
    Object* activeObject(std::string dataPool, std::string name);
    Object* activeRandomObject(std::string dataPool);

    void deleteObject(Object* deadEntity);
    void deleteAllActiveObject();

    // IDeadHandler을(를) 통해 상속됨
    void handleDeadEvent(Entity* deadEntity) override;

    // IUpdate을(를) 통해 상속됨
    void Update() override;
    int GetUpdatePriotity() override;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, Object*>> _objectDataPoolMap;
    std::vector<Object*> _activeObjects;
    // 업테이트중 삭제처리가 발생할 텐데 그러면 오류가 생김.
    // 실행중 제거라 UB?가 나타남. 따라서 이 메니져도 Update시키고, 그 update에서 제거하는 식으로 제거해야 안전할 듯
    std::queue<Object*> _toDeletedEntityQueue;
};

