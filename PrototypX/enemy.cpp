#include "Enemy.h"

Enemy::Enemy(float x, float y) : shape(sf::Vector2f(40, 40)) { 
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Blue);
}
