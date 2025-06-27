#pragma once

#include "Entity.h"

class IDeadHandler
{
public:
    virtual void handleDeadEvent(Entity* deadEntity) abstract;
};