#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "GameState.hpp"

extern std::vector<sf::Uint32> textBuffer;
extern char utilBuf[256];

extern sf::Time frameTime;
extern sf::Clock mainClock;
extern sf::RenderWindow mainWindow;
extern void setGameState(GameState *newState);
extern void getTextInput(sf::String &str);
extern void clearTextInputBuf();
extern int getRandInt(int min, int max);
extern bool hasKeyJustBeenPressed(sf::Keyboard::Key key);
extern bool hasKeyJustBeenReleased(sf::Keyboard::Key key);