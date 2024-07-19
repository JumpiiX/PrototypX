#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

#include "dot.h"
#include "map.h"
#include <SFML/Graphics.hpp>
#include <map>

class MovementController {
public:
    Dot& dot;
    const Map& map;
    std::map<sf::Keyboard::Key, bool> keys;
    float moveSpeed;

    MovementController(Dot& dot, const Map& map);
    void handleInput(float deltaTime);

private:
    bool checkCollision(const sf::Vector2f& position);
};

#endif
