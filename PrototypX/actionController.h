#ifndef ACTION_CONTROLLER_H
#define ACTION_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "enemy.h"

struct Projectile {
    sf::RectangleShape shape;
    sf::Vector2f direction;
    float speed;

    Projectile(sf::Vector2f pos, sf::Vector2f dir);
};

class ActionController {
public:
    std::vector<Projectile> projectiles;
    std::vector<Enemy> enemies;

    ActionController();
    void handleShooting(sf::RenderWindow& window, const sf::Vector2f& position);
    void updateProjectiles(sf::RenderWindow& window, float deltaTime);
    void updateEnemies(sf::RenderWindow& window);
    void drawProjectiles(sf::RenderWindow& window);
    void drawEnemies(sf::RenderWindow& window);
};

#endif
