#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "unistd.h"
#include <algorithm>
#include <iostream>
#include <type_traits>


// refactor such that rendering happens as VECTOR of int changes, give everything
// the same width and change origin if need be

void selection_sort(sf::RenderWindow& window, std::vector<sf::RectangleShape>& recs, int pos) {
    auto biggest = std::max_element(recs.begin() + pos, recs.end(), 
            [] (sf::RectangleShape const lhs, sf::RectangleShape const rhs) {
                return lhs.getSize().y < rhs.getSize().y;
            });
    // Issue is that biggest moves to end on screen but not within vector
    // technically you could map vector index to width position
    // then you would just need to swap vector indicies
    biggest->setFillColor(sf::Color::Red);
    for (auto i = biggest + 1; i < recs.end(); i++) {
        if (biggest == (recs.end() - pos)) break;
        const int testing = biggest->getPosition().x;
        const int next_to = i->getPosition().x;
        sf::Vector2f new_biggest = sf::Vector2f(next_to, biggest->getPosition().y);
        sf::Vector2f new_next = sf::Vector2f(testing, i->getPosition().y);
        biggest->setPosition(new_biggest);
        i->setPosition(new_next);
        i->setFillColor(sf::Color::Green);
        window.clear();
        for (auto r : recs) {
            window.draw(r);
        }
        window.display();
 
    }
}


int main()
{
    const int SCREEN_HEIGHT = 1000; 
    const int SCREEN_WIDTH = 1000;
    const int REC_WIDTH = 10;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hello World!");
    window.setVerticalSyncEnabled(true);

    std::vector<sf::RectangleShape> rectangles(SCREEN_WIDTH/REC_WIDTH);
    std::vector<int> rects(SCREEN_WIDTH/REC_WIDTH);
    int pos = 0;
    // providing seed value
    srand((unsigned) time(NULL));
    for (auto& r : rectangles) {
        int random = rand() % SCREEN_HEIGHT;
        rects.push_back(random);
        r = sf::RectangleShape(sf::Vector2f(REC_WIDTH, random));
        r.setFillColor(sf::Color::White);
        r.move((REC_WIDTH) * pos, (SCREEN_HEIGHT - random));
        // add outline, negative thickness adds outline inwards
        r.setOutlineThickness(-1.5);
        r.setOutlineColor(sf::Color::Black);
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
       selection_sort(window, rectangles, 0);
    }

    return 0;
}
