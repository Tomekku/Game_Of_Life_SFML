#ifndef SCENE_HPP
#define SCENE_HPP


#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <string>
#include "Enums.hpp"

/*
* interfejs dla każdej sceny aplikacji
*
*/

class Scene
{
public:
  virtual SimulationState start() = 0; //Metoda uruchamiająca pętlę sceny
  std::vector<sf::Text> getTexts() const { return _texts; } //Metoda dostępowa do pola std::vector<sf::Text> _texts
  std::vector<sf::VertexArray> getShapes() const {return _shapes; } //Metoda dostępowa do pola std::vector<sf::VertexArray> _shapes
  sf::Vector2i getMapSize(){  return mapSize; } //Metoda dostępowa do pola sf::Vector2i mapSize

protected:
  virtual void handleEvents() = 0; //Metoda odpowiedzialna za przechwytywanie eventów

  std::vector<sf::Text> _texts;
  std::vector<sf::VertexArray> _shapes;
  sf::Vector2i mapSize;
};

#endif //SCENE_HPP
