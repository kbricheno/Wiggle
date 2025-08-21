// Wiggle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    std::cout << "Hello World!\n";

    sf::RenderWindow window(sf::VideoMode({ 1600,900 }), "Wiggle", sf::Style::Default);
    while (window.isOpen()) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
            window.close();
        }
    }

    return 0;
}
