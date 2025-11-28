#include "Frontend.h"
#include "Backend.h"

void Frontend::Main_loop() {
    const int  width = 1801, height = 901;
    sf::RenderWindow window(sf::VideoMode(width, height), L"Урааа, сеточка какоето", sf::Style::Default);

    window.setVerticalSyncEnabled(true);

    sf::RectangleShape gridh;
    gridh.setSize(sf::Vector2f{width, 1});
    gridh.setPosition(sf::Vector2f{0, 0});
    gridh.setFillColor(sf::Color::Green);

    sf::RectangleShape gridv;
    gridv.setSize(sf::Vector2f{1, height});
    gridv.setPosition(sf::Vector2f{0, 0});
    gridv.setFillColor(sf::Color::Green);

    int pix_to_cm = 20;

    window.clear(sf::Color::Black);
    Frontend::Setochka(window, gridh, gridv, width, height, pix_to_cm);
    window.display();

    // основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    if (pix_to_cm < std::min(width, height)) {
                        pix_to_cm += 10;
                        window.clear(sf::Color::Black);
                        Frontend::Setochka(window, gridh, gridv, width, height, pix_to_cm);
                        window.display();
                    }
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    if (pix_to_cm > 10) {
                        pix_to_cm -= 10;
                        window.clear(sf::Color::Black);
                        Frontend::Setochka(window, gridh, gridv, width, height, pix_to_cm);
                        window.display();
                    }
                }
            }
        }
    }
}

void Frontend::Setochka(sf::RenderWindow& window, sf::RectangleShape gridh, sf::RectangleShape gridv, const int width, const int height, int pix_to_cm) {
    for (int i = height / 2; i < height; i += pix_to_cm) {
        gridh.setPosition(0, i);
        window.draw(gridh);
    }
    for (int i = height / 2; i >= 0; i -= pix_to_cm) {
        gridh.setPosition(0, i);
        window.draw(gridh);
    }

    for (int i = width / 2; i < width; i += pix_to_cm) {
        gridv.setPosition(i, 0);
        window.draw(gridv);
    }
    for (int i = width / 2; i >= 0; i -= pix_to_cm) {
        gridv.setPosition(i, 0);
        window.draw(gridv);
    }

    gridv.setFillColor(sf::Color::Yellow);
    gridv.setPosition(width / 2, 0);
    window.draw(gridv);
    gridh.setFillColor(sf::Color::Yellow);
    gridh.setPosition(0, height / 2);
    window.draw(gridh);

    sf::RectangleShape dot;
    dot.setSize(sf::Vector2f{1, 1});
    dot.setFillColor(sf::Color(255, 255, 255, 127));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int ret = Backend::Backend_func(i, j, width, height, pix_to_cm);
            if (ret > 0) {
                if (ret == 2) {
                    dot.setFillColor(sf::Color(255, 255, 255));
                }
                else if (ret == 1) {
                    dot.setFillColor(sf::Color(255, 255, 255, 127));
                }
                dot.setPosition(sf::Vector2f{float(i), float(j)});
                window.draw(dot);
            }
        }
    }
}