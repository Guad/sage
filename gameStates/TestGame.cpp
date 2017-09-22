#include "TestGame.hpp"
#include "GameOverState.hpp"
#include <vector>
#include <cmath>

struct player_state
{
    sf::Shape *shape;
};

struct enemy_state
{
    sf::Shape *shape;
    int dirx, dirY;
    bool hasEntered;
};

player_state player;
std::vector<enemy_state> enemies;
std::vector<enemy_state> bullets;

void TestGame::Draw()
{
    for (auto i = enemies.begin(); i < enemies.end(); ++i)
    {
        mainWindow.draw(*i->shape);
    }

    for (auto i = bullets.begin(); i < bullets.end(); ++i)
    {
        mainWindow.draw(*i->shape);
    }

    mainWindow.draw(*player.shape);
}

const float speed = 200;
const float rotSpeed = 200;
const int maxEnemies = 10;
sf::Time lastEnemySpawn;
const int enemySpawnRate = 1000;

void createBullet()
{
    const int enemyRadius = 5;
    const int enspeed = 500;

    sf::CircleShape *shape = new sf::CircleShape(enemyRadius);
    int dirX, dirY;

    int randAngle = player.shape->getRotation() - 45;
    float toRad = 3.14159f / 180.f;

    dirX = std::cos(randAngle * toRad) * enspeed;
    dirY = std::sin(randAngle * toRad) * enspeed;

    shape->setFillColor(sf::Color::Red);
    shape->setOrigin(enemyRadius, enemyRadius);
    shape->setPosition(player.shape->getPosition());

    bullets.push_back({ shape, dirX, dirY });
}

void updatePlayer()
{
    sf::Vector2f vel(0,0);
    float angle = player.shape->getRotation() - 45;
    float toRad = 3.14159f / 180.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        float movPerFrame = speed * frameTime.asSeconds();
        vel.x += std::cos(angle * toRad) * movPerFrame;
        vel.y += std::sin(angle * toRad) * movPerFrame;
    }

    player.shape->move(vel);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        player.shape->rotate(rotSpeed * frameTime.asSeconds());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        player.shape->rotate(-rotSpeed * frameTime.asSeconds());
    }

    if (hasKeyJustBeenPressed(sf::Keyboard::Space))
    {
        createBullet();
    }
}

void createEnemy()
{
    const int enemyRadius = 30;
    const int enspeed = 300;

    sf::CircleShape *shape = new sf::CircleShape(enemyRadius);
    int dirX, dirY;

    int randAngle = getRandInt(0, 360);
    float toRad = 3.14159f / 180.f;

    dirX = std::cos(randAngle * toRad) * enspeed;
    dirY = std::sin(randAngle * toRad) * enspeed;

    shape->setFillColor(sf::Color::Blue);
    shape->setOrigin(enemyRadius, enemyRadius);
    shape->setPosition(400 - dirX * 1.5f, 300 - dirY * 1.5f);

    enemies.push_back({ shape, dirX, dirY, false });
}

void updateEnemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].shape->move(enemies[i].dirx * frameTime.asSeconds(), enemies[i].dirY * frameTime.asSeconds());
        auto pos = enemies[i].shape->getPosition();
        if (enemies[i].shape->getGlobalBounds().intersects(player.shape->getGlobalBounds()))
        {
            setGameState(new GameOverState("Game Over!"));
            //mainWindow.close();
            // TODO: You lost!
            // TODO: Vidas
            return;
        }

        if (pos.x < 0 || pos.x > 900 || pos.y < 0 || pos.y > 700)
        {
            if (enemies[i].hasEntered)
                enemies.erase(enemies.begin() + i);
        }
        else if (!enemies[i].hasEntered)
            enemies[i].hasEntered = true;

        for (int j = 0; j < bullets.size(); j++)
        {
            if (enemies[i].shape->getGlobalBounds().contains(bullets[j].shape->getPosition()))
            {
                enemies.erase(enemies.begin() + i);
                bullets.erase(bullets.begin() + j);
            }
        }
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].shape->move(bullets[i].dirx * frameTime.asSeconds(), bullets[i].dirY * frameTime.asSeconds());
        auto pos = bullets[i].shape->getPosition();
        
        if (pos.x < 0 || pos.x > 900 || pos.y < 0 || pos.y > 700)
            bullets.erase(bullets.begin() + i);
    }

    if (enemies.size() < maxEnemies &&
        mainClock.getElapsedTime().asMilliseconds() - lastEnemySpawn.asMilliseconds() >  enemySpawnRate)
    {
        lastEnemySpawn = mainClock.getElapsedTime();
        
        createEnemy();
    }
}


void TestGame::Update()
{
    updatePlayer();
    updateEnemies();
}

void TestGame::Enter()
{
    const int size = 50;

    player.shape = new sf::RectangleShape(sf::Vector2f(size, size));
    player.shape->setFillColor(sf::Color::Red);
    player.shape->setOrigin(size / 2, size / 2);
    player.shape->setRotation(45);
    player.shape->setPosition(400, 300);

    lastEnemySpawn = mainClock.getElapsedTime();
}

void TestGame::Leave()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        delete enemies[i].shape;
    }

    for (int i = 0; i < bullets.size(); i++)
    {
        delete bullets[i].shape;
    }

    enemies.clear();
    bullets.clear();
    
    delete player.shape;
}

TestGame::~TestGame()
{
}

TestGame::TestGame()
{
}