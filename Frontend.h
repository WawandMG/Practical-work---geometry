#pragma once
#include <SFML/Graphics.hpp>
namespace Frontend {
	void Main_loop();
    void Setochka(sf::RenderWindow& window, sf::RectangleShape gridh, sf::RectangleShape gridv, const int width, const int hight, int pix_to_cm);
};
