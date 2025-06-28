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

    // IDeadHandler��(��) ���� ��ӵ�
    void handleDeadEvent(Entity* deadEntity) override;

    // IUpdate��(��) ���� ��ӵ�
    void Update() override;
    int GetUpdatePriotity() override;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, Object*>> _objectDataPoolMap;
    std::vector<Object*> _activeObjects;
    // ������Ʈ�� ����ó���� �߻��� �ٵ� �׷��� ������ ����.
    // ������ ���Ŷ� UB?�� ��Ÿ��. ���� �� �޴����� Update��Ű��, �� update���� �����ϴ� ������ �����ؾ� ������ ��
    std::queue<Object*> _toDeletedEntityQueue;
};

