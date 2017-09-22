#include "GameOverState.hpp"
#include "TestGame.hpp"

void GameOverState::Draw()
{
    drawText(_text, 400, 300, 46, sf::Color::Red, 0, 1);
}


void GameOverState::Update()
{
    if (hasKeyJustBeenPressed(sf::Keyboard::Key::R))
    {
        setGameState(new TestGame());
    }
}

void GameOverState::Enter()
{

}

void GameOverState::Leave()
{
    
}

GameOverState::~GameOverState()
{
}

GameOverState::GameOverState()
{
}

GameOverState::GameOverState(sf::String str)
{
    this->_text = str;
}