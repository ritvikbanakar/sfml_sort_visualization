// starting from scratch using ints and rendering rectangles as dependent 

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <iostream>
 const int SCREEN_HEIGHT = 1000;
 const int SCREEN_WIDTH = 1000;
 const int REC_WIDTH = 10;

 void render(sf::RenderWindow& window, std::vector<int> vals) {
    window.clear();
    int pos = 0;
    for (int i : vals) {
        sf::RectangleShape r = sf::RectangleShape(sf::Vector2f(REC_WIDTH, i));
        r.setFillColor(sf::Color::White);
        r.move((REC_WIDTH) * pos, (SCREEN_HEIGHT - i));
        // add outline, negative thickness adds outline inwards
        r.setOutlineThickness(-1.5);
        r.setOutlineColor(sf::Color::Black);
        pos++;
        window.draw(r);
    }
    window.display();
}

void selection_sort(sf::RenderWindow& window, std::vector<int>& recs, int pos) {
    if (pos >= recs.size()) return;
    auto biggest = std::max_element(recs.begin(), recs.end() - pos);
    //std::cout << *biggest << std::endl;
    int idx_big = std::distance(recs.begin(), biggest);
    for (int i = idx_big + 1; i < recs.size(); i++) {
     //   std::cout << "looping" << std::endl;
        if (idx_big == (recs.size() - pos)) break;
        int temp = recs.at(idx_big); 
        recs.at(idx_big) = recs.at(idx_big + 1);
        recs.at(idx_big + 1) = temp;
      //  std::cout << "new vals: " << recs.at(idx_big) << " " << recs.at(idx_big + 1) 
      //     << std::endl;
        idx_big++;
        render(window, recs);
    }
    //std::cout << recs.at(recs.size() - 1) << std::endl;
    selection_sort(window, recs, pos + 1);
}

int main() {
    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hello World!");
    window.setVerticalSyncEnabled(true);

    std::vector<int> rectangles(SCREEN_WIDTH/REC_WIDTH);
    int pos = 0;

    srand((unsigned) time(NULL));
    for (int& r : rectangles) { 
        r = rand() % SCREEN_HEIGHT;
    }

        while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        render(window, rectangles);
        selection_sort(window, rectangles, 0);

        window.display();
    }
    return 0;

}
