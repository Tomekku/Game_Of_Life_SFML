#ifndef CELL_SET_SCENE_HPP
#define CELL_SET_SCENE_HPP

#include "Scene.hpp"
#include "Renderer.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

/*
* implementacja interfejsu Scene dla ekranu ustawiania komórek
*/

class CellSetScene : public SceneMap
{
public:
  CellSetScene(Renderer *renderer, SimulationState& state, bool** &map, int const mapSizeX, int const mapSizeY); //Konstruktor
  SimulationState start() override; //Nadpisana metoda uruchamiająca pętlę sceny
  bool** exportMap(); //Metoda odpowiedzialna za eksport utworzonej mapy
  ~CellSetScene(); //Destruktor

private:
  void handleEvents() override; //Nadpisana metoda odpowiedzialna za przechwytywanie eventów
  void processMapEvents(); //Metoda odpowiedzialna za przetwarzanie eventów
  void processClickEvent(); //Metoda obsługująca akcje działające po wybraniu przycisku myszy
  void toggleCell(int i, int j); //Metoda odpowiedzialna za zmianę stanu komórki
  void generateTexts(); //Metoda odpowiedzialna za generowanie napisów
  void generateShape(); //Metoda odpowiedzialna za generowanie kształtów
  void generateMap(); //Metoda odpowiedzialna za generowanie pustej mapy
  int getRectSide(); //Metoda odpowiedzialna za przeliczanie krawędzi kwadratu

  Renderer *_renderer; //Wskaźnik na obiekt Renderer
  SimulationState _state; //Zmienna przechowująca obecny stan symulacji
  const int _MAP_SIZE_X; //stała przechowująca szerokość mapy
  const int _MAP_SIZE_Y; //stała przechowująca wysokość mapy
  const int _WINDOW_CORRECTION; //stała przechowująca przesunięcie mapy względem punktu (0,0) na ekranie
  bool **_boolMap; //Wskaźnik na tablicę dwuwymiarową mapy
  sf::Vector2i mousePosition; //Zmienna przechowująca współrzędne wskaźnika myszy
};

#endif //CELL_SET_SCENE_HPP
