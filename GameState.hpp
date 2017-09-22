#pragma once

#include <SFML/Graphics.hpp>

class GameState
{
public:
    virtual ~GameState() {}

    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual void Enter() = 0;
    virtual void Leave() = 0;
};