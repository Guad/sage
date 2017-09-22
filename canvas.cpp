#include "canvas.hpp"
#include <cmath>

sf::Font DEFAULT_FONT;

void drawText(sf::String text, int x, int y, int size, sf::Color color, float rot, int justify)
{
    sf::Text label;

    label.setString(text);
    label.setFont(DEFAULT_FONT);
    label.setCharacterSize(size);
    label.setFillColor(color);
    label.setPosition(x, y);
    label.setRotation(rot);

    switch(justify)
    {
        case 1: // Center
            label.setPosition(x - label.getGlobalBounds().width * 0.5f, y);
            break;
        case 2: // Right
            label.setPosition(x - label.getGlobalBounds().width, y);
            break;
    }
    
    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();

    mainWindow.setView(defaultView);
    mainWindow.draw(label);

    mainWindow.setView(oldView);
}

void drawPixels(sf::Uint8 *pixels, int x, int y, int w, int h)
{
    sf::Texture text;
    sf::Sprite sprite;
    
    text.create(w, h);
    text.update(pixels);
    
    sprite.setPosition(x, y);
    sprite.setTexture(text);
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));

    
    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();
    
    mainWindow.setView(defaultView);
    mainWindow.draw(sprite);

    mainWindow.setView(oldView);
}

void drawTexture(sf::Texture &texture, int x, int y, float scale, sf::Color color, float rot)
{
    sf::Sprite sprite;

    auto size = texture.getSize();

    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setRotation(rot);
    sprite.setScale(scale, scale);
    sprite.setColor(color);

    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();
    
    mainWindow.setView(defaultView);
    mainWindow.draw(sprite);

    mainWindow.setView(oldView);    
}

void drawTexture(sf::Texture &texture, int x, int y, float scaleX, float scaleY, sf::Color color, float rot)
{
    sf::Sprite sprite;

    auto size = texture.getSize();

    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setRotation(rot);
    sprite.setScale(scaleX, scaleY);
    sprite.setColor(color);

    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();
    
    mainWindow.setView(defaultView);
    mainWindow.draw(sprite);

    mainWindow.setView(oldView);
}

void drawRectangle(int x, int y, int w, int h, sf::Color color, float rot)
{
    sf::RectangleShape sprite;
    
    sprite.setOrigin(w / 2, h / 2);
    sprite.setPosition(x, y);
    sprite.setSize(sf::Vector2f(w, h));
    sprite.setRotation(rot);
    sprite.setFillColor(color);

    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();
    
    mainWindow.setView(defaultView);
    mainWindow.draw(sprite);

    mainWindow.setView(oldView);    
}

void drawBounds(int x, int y, int w, int h, sf::Color color, float rot, int thick)
{
    sf::RectangleShape sprite;
    
    sprite.setOrigin(w / 2, h / 2);
    sprite.setPosition(x, y);
    sprite.setSize(sf::Vector2f(w, h));
    sprite.setRotation(rot);
    sprite.setFillColor(sf::Color::Transparent);
    sprite.setOutlineThickness(thick);
    sprite.setOutlineColor(color);

    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();
    
    mainWindow.setView(defaultView);
    mainWindow.draw(sprite);

    mainWindow.setView(oldView);    
}

void drawCircle(int x, int y, int radius, sf::Color color, float rot)
{
    sf::CircleShape sprite;
    
    sprite.setOrigin(radius, radius);
    sprite.setPosition(x, y);
    sprite.setRadius(radius);
    sprite.setRotation(rot);
    sprite.setFillColor(color);

    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();
    
    mainWindow.setView(defaultView);
    mainWindow.draw(sprite);

    mainWindow.setView(oldView);    
}

void drawLine(int startX, int startY, int endX, int endY, int width, sf::Color color)
{
    sf::Vertex vertices[4];

    sf::Vector2f point1(startX, startY);
    sf::Vector2f point2(endX, endY);

    sf::Vector2f direction = point2 - point1;
    sf::Vector2f unitDirection = direction/std::sqrt(direction.x*direction.x+direction.y*direction.y);
    sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    sf::Vector2f offset = (width/2.f)*unitPerpendicular;

    vertices[0].position = point1 + offset;
    vertices[1].position = point2 + offset;
    vertices[2].position = point2 - offset;
    vertices[3].position = point1 - offset;

    for (int i = 0; i < 4; ++i)
        vertices[i].color = color;

    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();
    
    mainWindow.setView(defaultView);
    mainWindow.draw(vertices, 4, sf::Quads);

    mainWindow.setView(oldView);    
}

sf::Vector2f getResolution()
{
    return mainWindow.getView().getSize();
}



void drawTextWorld(sf::String text, int x, int y, int size, sf::Color color, float rot, int justify)
{
    sf::Text label;

    label.setString(text);
    label.setFont(DEFAULT_FONT);
    label.setCharacterSize(size);
    label.setFillColor(color);
    label.setPosition(x, y);
    label.setRotation(rot);

    switch(justify)
    {
        case 1: // Center
            label.setPosition(x - label.getGlobalBounds().width * 0.5f, y);
            break;
        case 2: // Right
            label.setPosition(x - label.getGlobalBounds().width, y);
            break;
    }
    
    mainWindow.draw(label);
}

void drawPixelsWorld(sf::Uint8 *pixels, int x, int y, int w, int h)
{
    sf::Texture text;
    sf::Sprite sprite;
    
    text.create(w, h);
    text.update(pixels);
    
    sprite.setPosition(x, y);
    sprite.setTexture(text);
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));

    mainWindow.draw(sprite);
}

void drawTextureWorld(sf::Texture &texture, int x, int y, float scale, sf::Color color, float rot)
{
    sf::Sprite sprite;

    auto size = texture.getSize();

    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setRotation(rot);
    sprite.setScale(scale, scale);
    sprite.setColor(color);

    mainWindow.draw(sprite);
}

void drawTextureWorld(sf::Texture &texture, int x, int y, float scaleX, float scaleY, sf::Color color, float rot)
{
    sf::Sprite sprite;

    auto size = texture.getSize();

    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setRotation(rot);
    sprite.setScale(scaleX, scaleY);
    sprite.setColor(color);

    mainWindow.draw(sprite);
}

void drawRectangleWorld(int x, int y, int w, int h, sf::Color color, float rot)
{
    sf::RectangleShape sprite;
    
    sprite.setOrigin(w / 2, h / 2);
    sprite.setPosition(x, y);
    sprite.setSize(sf::Vector2f(w, h));
    sprite.setRotation(rot);
    sprite.setFillColor(color);

    mainWindow.draw(sprite);
}

void drawBoundsWorld(int x, int y, int w, int h, sf::Color color, float rot, int thick)
{
    sf::RectangleShape sprite;
    
    sprite.setOrigin(w / 2, h / 2);
    sprite.setPosition(x, y);
    sprite.setSize(sf::Vector2f(w, h));
    sprite.setRotation(rot);
    sprite.setFillColor(sf::Color::Transparent);
    sprite.setOutlineThickness(thick);
    sprite.setOutlineColor(color);
    
    mainWindow.draw(sprite);
}

void drawCircleWorld(int x, int y, int radius, sf::Color color, float rot)
{
    sf::CircleShape sprite;
    
    sprite.setOrigin(radius, radius);
    sprite.setPosition(x, y);
    sprite.setRadius(radius);
    sprite.setRotation(rot);
    sprite.setFillColor(color);

    mainWindow.draw(sprite);
}

void drawLineWorld(int startX, int startY, int endX, int endY, int width, sf::Color color)
{
    sf::RectangleShape sprite;

    sf::Vector2f point1(startX, startY);
    sf::Vector2f point2(endX, endY);

    sf::Vector2f direction = point2 - point1;
    float length = std::sqrt(direction.x*direction.x+direction.y*direction.y);
    //sf::Vector2f unitDirection = direction / length;
    //sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

    //sf::Vector2f offset = (width/2.f)*unitPerpendicular;

    sprite.setSize(sf::Vector2f(width, length));
    sprite.setOrigin(sf::Vector2f(width / 2, 0));
    sprite.setPosition(point1);
    sprite.setFillColor(color);

    const float pi = 3.14159265358979323846f;

    float angleRad = std::atan2(direction.y, direction.x);
    float angleDeg = angleRad * (180.f / pi);

    if (angleDeg < 0)
        angleDeg += 360;

    sprite.setRotation(angleDeg - 90);

    auto defaultView = mainWindow.getDefaultView();
    auto oldView = mainWindow.getView();
   
    mainWindow.setView(defaultView);
    mainWindow.draw(sprite);

    mainWindow.setView(oldView);    
}