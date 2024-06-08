// main.cpp
#include <SFML/Graphics.hpp>
#include "dot.h"
#include "movementController.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "PrototypX.exe");
    Dot dot(960, 540); // Startposition in der Mitte
    MovementController controller(dot);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                controller.handleInput(event.key.code);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(dot.shape);
        window.display();
    }

    return 0;
}
