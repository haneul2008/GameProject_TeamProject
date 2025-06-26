#pragma once

class Entity;

class IDamageable
{
public:
    virtual void takeDamage(Entity* dealer, int damage) abstract;
};