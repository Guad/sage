#include "globals.hpp"
#include "canvas.hpp"

#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>

#define INIT_GAME_STATE

#ifdef INIT_GAME_STATE
#include "gameStates/TestState.hpp"
#include "gameStates/TestGame.hpp"
#endif


std::vector<sf::Uint32> textBuffer;
char utilBuf[256];
std::vector<sf::Keyboard::Key> pressedKeys;
std::vector<sf::Keyboard::Key> releasedKeys;

sf::RenderWindow mainWindow;
sf::Clock mainClock;
sf::Time frameTime = sf::seconds(0.016f);

GameState *currentState;

int main()
{
    srand(time(NULL));

    mainWindow.create(sf::VideoMode(800, 600), "SFML works!", sf::Style::Titlebar | sf::Style::Close);

    mainWindow.setPosition(sf::Vector2i(20, 50));
    mainWindow.setKeyRepeatEnabled(false);

    //mainWindow.setVerticalSyncEnabled(true);
    // Use either one
    mainWindow.setFramerateLimit(60);

    DEFAULT_FONT.loadFromFile("typewriter.ttf");

#ifdef INIT_GAME_STATE
    setGameState(new TestGame());
#endif
    char newtitle[256];
    sf::Clock lastFrame;

    
    while (mainWindow.isOpen())
    {
        pressedKeys.clear();
        releasedKeys.clear();

        frameTime = lastFrame.getElapsedTime();
        lastFrame.restart();

        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                mainWindow.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                textBuffer.push_back(event.text.unicode);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                pressedKeys.push_back(event.key.code);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                releasedKeys.push_back(event.key.code);
            }
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                // event.mouseWheelScroll
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // event.mouseButton
                // sf::Mouse::Right
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
            }
        }

        if (currentState != nullptr)
            currentState->Update();

        sprintf(newtitle, "FPS: %f", 1.0f/frameTime.asSeconds());

        mainWindow.setTitle(newtitle);

        mainWindow.clear(sf::Color::Black);

        if (currentState != nullptr)
            currentState->Draw();

        mainWindow.display();
    }

    return 0;
}

void setGameState(GameState *state)
{
    if (currentState != nullptr)
    {
        currentState->Leave();
        delete currentState;
        currentState = nullptr;
    }

    if (state == nullptr)
        return;

    state->Enter();

    currentState = state;
}

void getTextInput(sf::String &str)
{
    str.clear();

    if (textBuffer.size() == 0)
        return;

    str.fromUtf32(textBuffer.begin(), textBuffer.end());

    textBuffer.clear();
}

void clearTextInputBuf()
{
    textBuffer.clear();
}

int getRandInt(int min, int max)
{
    return min + rand() % (max - min);
}

bool hasKeyJustBeenPressed(sf::Keyboard::Key key)
{
    for (auto i = pressedKeys.begin(); i < pressedKeys.end(); ++i)
        if (key == *i)
            return true;
}

bool hasKeyJustBeenReleased(sf::Keyboard::Key key)
{
    for (auto i = releasedKeys.begin(); i < releasedKeys.end(); ++i)
        if (key == *i)
            return true;
}