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
    void addEntityData(std::string dataPool, std::string name, Entity*&& entity);
    Entity* getEntityData(std::string dataPool, std::string name);
    Entity* activeEntity(std::string dataPool, std::string name);
    Entity* activeRandomEntity(std::string dataPool);

    void deleteEntity(Entity* deadEntity);

    // IDeadHandler��(��) ���� ��ӵ�
    void handleDeadEvent(Entity* deadEntity) override;

    // IUpdate��(��) ���� ��ӵ�
    void Update() override;
    int GetUpdatePriotity() override;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, Entity*>> _entityDataPoolMap;
    std::vector<Entity*> _activeEntities;
    // ������Ʈ�� ����ó���� �߻��� �ٵ� �׷��� ������ ����.
    // ������ ���Ŷ� UB?�� ��Ÿ��. ���� �� �޴����� Update��Ű��, �� update���� �����ϴ� ������ �����ؾ� ������ ��
    std::queue<Entity*> _toDeletedEntityQueue;
};

