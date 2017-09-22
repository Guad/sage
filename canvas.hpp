#pragma once

#include <SFML/Graphics.hpp>
#include "globals.hpp"

extern sf::Font DEFAULT_FONT;

sf::Vector2f getResolution();

void drawText(sf::String text, int x, int y, int size, sf::Color color, float rot, int justify);
void drawPixels(sf::Uint8 *pixels, int x, int y, int w, int h);
void drawTexture(sf::Texture &texture, int x, int y, float scale, sf::Color color, float rot);
void drawTexture(sf::Texture &texture, int x, int y, float scaleX, float scaleY, sf::Color color, float rot);
void drawRectangle(int x, int y, int w, int h, sf::Color color, float rot);
void drawBounds(int x, int y, int w, int h, sf::Color color, float rot, int thick);
void drawCircle(int x, int y, int radius, sf::Color color);
void drawLine(int startX, int startY, int endX, int endY, int width, sf::Color color);

void drawTextWorld(sf::String text, int x, int y, int size, sf::Color color, float rot, int justify);
void drawPixelsWorld(sf::Uint8 *pixels, int x, int y, int w, int h);
void drawTextureWorld(sf::Texture &texture, int x, int y, float scale, sf::Color color, float rot);
void drawTextureWorld(sf::Texture &texture, int x, int y, float scaleX, float scaleY, sf::Color color, float rot);
void drawRectangleWorld(int x, int y, int w, int h, sf::Color color, float rot);
void drawBoundsWorld(int x, int y, int w, int h, sf::Color color, float rot, int thick);
void drawCircleWorld(int x, int y, int radius, sf::Color color);
void drawLineWorld(int startX, int startY, int endX, int endY, int width, sf::Color color);
