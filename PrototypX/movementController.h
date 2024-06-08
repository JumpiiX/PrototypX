#pragma once
// physics/MovementController.h
#ifndef MOVEMENT_CONTROLLER_H
#define MOVEMENT_CONTROLLER_H

#include "Dot.h"

class MovementController {
public:
    Dot& dot;

    MovementController(Dot& dot);
    void handleInput(const sf::Keyboard::Key& key);
};

#endif
