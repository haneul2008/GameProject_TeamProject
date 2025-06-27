#pragma once

#include "Entity.h"

class IDeadHandler
{
public:
    void handleDeadEvent(Entity* deadEntity);
};