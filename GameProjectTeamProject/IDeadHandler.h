#pragma once

class Entity;

class IDeadHandler
{
public:
    virtual void handleDeadEvent(Entity* deadEntity) abstract;
};