#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

#include "dot.h"
#include <SFML/Graphics.hpp>
#include <map>

class MovementController {
public:
    Dot& dot;
    std::map<sf::Keyboard::Key, bool> keys;
    float moveSpeed;

    MovementController(Dot& dot);
    void handleInput(float deltaTime);
};

#endif
