#pragma once

#include <vector>
#include "Entity.h"
#include "TurnManager.h"

class Enemy : public virtual Entity, public virtual ITurnListener
{
public:
    void init(EntityStat stat, wchar_t defaultImage, bool trigger, int layer) override;
    virtual void active() override;

    // ITurnListener을(를) 통해 상속됨
    void handlePlayerTurn() override;
    void handleEnemyTurn() override;

    void onHitEvent(Entity* dealer, int damage) override;
    void onDeadEvent(Entity* dealer, int damage) override;

    void addDeadMessage(std::string message);

protected:
    std::string getDeadMessage();

private:
    std::vector<std::string> _deadMassages;
};

