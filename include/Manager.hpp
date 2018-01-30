#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Scene.hpp"
#include "Enums.hpp"
#include "Map.hpp"
#include "MainScene.hpp"
#include "Renderer.hpp"
#include "ConfigurationScene.hpp"
#include "CellSetScene.hpp"
#include "SimulationScene.hpp"
#include "ResultsScene.hpp"
#include "ImportScene.hpp"
#include <iostream>

/*
* Klasa zarządzająca działaniem aplikacji
*/

class Manager
{
public:
  Manager(sf::RenderWindow *window, sf::Font *font); //Konstruktor
  ~Manager(); //Destruktor
  void start(); //Metoda uruchamiająca główną pętlę stanów gry

private:
  Renderer *_renderer; //Wskaźnik na obiekt Renderer
  SimulationState _state; //Zmienna przechowująca obecny stan symulacji
  Scene *_scene; //Wskażnik na obiekt typu Scene

  sf::Vector2i _mapSize; //Zmienna przechowująca rozmiar mapy

  int _generationCount; //Zmienna przechowująca liczbę pokoleń
  int _aliveCellCount; //Zmienna przechowująca liczbę żywych komórek

};

#endif //MANAGER_HPP
