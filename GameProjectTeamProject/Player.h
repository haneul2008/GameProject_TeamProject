#pragma once

#include "Entity.h"
#include "IInputable.h"

class Player : virtual public Entity, virtual public IInputable
{
public:
    Player();

public:
    virtual void init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) override;

    void setWhatIsItemLayer(int layer);
    void setWhatIsWallLayer(int layer);
    void setWhatIsEnemyLayer(int layer);

    void applyMove() override;

    // IInputable��(��) ���� ��ӵ�
    void onInputKey(Key key) override;
    void setInputLock(bool value);

private:
    void onTriggerEvent(Collider& other, const Pos& newPosition) override;
    void onCollisionEvent(Collider& other, const Pos& newPosition) override;
    void attack(Entity* target, int damage);
    // ���� ������ �ʿ䰡 ���ٰ� ����. ��� �����ϴ� �޸𸮸� Ŀ�� ��
    std::string getAttackComment();

private:
    bool _inputLock;

private:
    int _whatIsItem;
    int _whatIsWall;
    int _whatIsEnemy;
};