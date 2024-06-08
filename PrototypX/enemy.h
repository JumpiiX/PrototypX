#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    sf::RectangleShape shape;

    Enemy(float x, float y);
};

#endif
