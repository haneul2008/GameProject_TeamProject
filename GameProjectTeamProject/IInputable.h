#pragma once

#include "TempEnums.h"

class IInputable
{
public:
    virtual void onInputKey(Key key) = 0;
};