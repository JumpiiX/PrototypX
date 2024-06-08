#pragma once
// models/Dot.h
#ifndef DOT_H
#define DOT_H

#include <SFML/Graphics.hpp>

class Dot {
public:
    sf::CircleShape shape;

    Dot(float x, float y);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
};

#endif
