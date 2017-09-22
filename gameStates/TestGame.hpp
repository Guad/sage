#pragma once

#include "../GameState.hpp"
#include "../globals.hpp"
#include "../canvas.hpp"

class TestGame : public GameState
{
public:
    TestGame();
    ~TestGame();
    void Update();
    void Draw();
    void Enter();
    void Leave();
};