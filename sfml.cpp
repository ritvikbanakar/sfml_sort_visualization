#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
int main()
{
    const int SCREEN_HEIGHT = 1000; 
    const int SCREEN_WIDTH = 1000;
    // TODO: adjust number of rectangles chosen to screen size
    std::vector<sf::RectangleShape> rectangles(18);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hello World!");
    int pos = 0;
    // providing seed value
    srand((unsigned) time(NULL));
    for (auto& r : rectangles) {
        int random = rand() % SCREEN_HEIGHT;
        r = sf::RectangleShape(sf::Vector2f(50, random));
        r.setFillColor(sf::Color::White);
        r.move(55 * pos, (SCREEN_HEIGHT - random));
        pos++;
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto r : rectangles) {
            window.draw(r);
        }
        window.display();
    }

    return 0;
}
