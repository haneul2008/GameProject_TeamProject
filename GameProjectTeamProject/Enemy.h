#pragma once

#include <vector>
#include "Entity.h"
#include "Player.h"
#include "TurnManager.h"

class Enemy : public virtual Entity, public virtual ITurnListener, public virtual IDeadHandler
{
public:
    ~Enemy() override;
    virtual Enemy* newClone() override;

public:
    void init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) override;
    virtual void active() override;
    virtual void deActive() override;

    void Render() override;

    // ITurnListener을(를) 통해 상속됨
    void handlePlayerTurn() override;
    void handleEnemyTurn() override;

    void onHitEvent(Entity* dealer, int damage) override;
    void onDeadEvent(Entity* dealer, int damage) override;

    void addDeadMessage(std::string message);

    void setPlayer(Player* player);
    void setSenceRange(int range);

    virtual void onCollisionEvent(Collider& other, const Pos& beforePosition) override;

    // IDeadHandler을(를) 통해 상속됨
    void handleDeadEvent(Entity* deadEntity) override;
    void setWallLayer(int layer);

protected:
    std::string getDeadMessage();
    bool sencePlayerInSenceRange();
    Pos getMoveToPlayerPos();

private:
    std::vector<std::string> _deadMassages;
    Player* _pPlayer;
    int _senceRange;
    int _whatIsWall;
};

