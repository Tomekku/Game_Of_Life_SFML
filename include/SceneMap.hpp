#ifndef SCENE_MAP_HPP
#define SCENE_MAP_HPP

#include "Scene.hpp"
#include <SFML/Graphics.hpp>

/*
* Klasa rozszerzająca klasę Scene o pole przechowujące mapę
*/

class SceneMap : public Scene
{
public:
  std::vector<std::vector<sf::RectangleShape>>  getMap() { return _map; } //Metoda dostępowa do pola std::vector<std::vector<sf::RectangleShape>> _map

protected:
  std::vector<std::vector<sf::RectangleShape>> _map;
};

#endif //SCENE_MAP_HPP
