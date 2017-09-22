#pragma once
#include <SFML/Graphics.hpp>
#include "../GameState.hpp"
#include "../globals.hpp"
#include "../canvas.hpp"

class GameOverState : public GameState
{
public:
    GameOverState();
    GameOverState(sf::String str);
    ~GameOverState();
    void Update();
    void Draw();
    void Enter();
    void Leave();
private:
    sf::String _text;
};