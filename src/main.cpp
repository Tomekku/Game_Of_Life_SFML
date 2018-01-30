#include <iostream>
#include "../include/Manager.hpp"

int main() {
  try
  {
    sf::RenderWindow window(sf::VideoMode(1280,720),"Game of Life", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Font font;
  	if(!font.loadFromFile("../res/Orbitron/Orbitron-Regular.ttf"))
  			return 1;

    Manager manager(&window, &font);
    manager.start();
  }
  catch(const std::exception& ex)
  {
    std::cout << "Error occurred: " << ex.what() << std::endl;
  }
  return 0;
}
