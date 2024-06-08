#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "dot.h"
#include "movementController.h"
#include "enemy.h"
#include "actionController.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PrototypX.exe");
    window.setMouseCursorVisible(false); 

    Dot dot(960, 540); 
    MovementController controller(dot);
    ActionController actionController;

    std::srand(std::time(nullptr)); 
    sf::Clock clock;

  
    controller.keys[sf::Keyboard::W] = false;
    controller.keys[sf::Keyboard::A] = false;
    controller.keys[sf::Keyboard::S] = false;
    controller.keys[sf::Keyboard::D] = false;

    while (window.isOpen()) {
        sf::Event event;
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                controller.keys[event.key.code] = true;
            }

            if (event.type == sf::Event::KeyReleased) {
                controller.keys[event.key.code] = false;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                actionController.handleShooting(window, dot.getPosition());
            }
        }

        controller.handleInput(deltaTime);

        actionController.updateProjectiles(window, deltaTime);

        window.clear(sf::Color::Black);
        window.draw(dot.shape);
        actionController.drawEnemies(window);
        actionController.drawProjectiles(window);
        window.display();
    }

    return 0;
}
