#ifndef SIMULATIONSCENE_HPP
#define SIMULATIONSCENE_HPP


#include "Scene.hpp"
#include "Renderer.hpp"
#include "Enums.hpp"
#include "Map.hpp"
#include "File.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <ctime>

/*
* implementacja interfejsu Scene dla ekranu symulacji
*/

class SimulationScene : public SceneMap
{
public:
  SimulationScene(Renderer *renderer, SimulationState& state, bool** map, sf::Vector2i& mapSize, int *generationCount); //Konstruktor
  SimulationState start() override; //Nadpisana metoda uruchamiająca pętlę sceny
  ~SimulationScene(); //Destruktor

private:
  void handleEvents() override; //Nadpisana metoda odpowiedzialna za przechwytywanie eventów
  void processClickEvent(); //Metoda obsługująca akcje działające po wybraniu przycisku myszy
  void generateTexts(); //Metoda odpowiedzialna za generowanie napisów
  void generateShape(); //Metoda odpowiedzialna za generowanie kształtów
  void generateMap(); //Metoda odpowiedzialna za generowanie pustej mapy
  int getRectSide(); //Metoda odpowiedzialna za przeliczanie krawędzi kwadratu
  void logCurrentState(); //Metoda odpowiedzialna za logowanie stanu symulacji

  Renderer *_renderer; //Wskaźnik na obiekt Renderer
  SimulationState _state; //Zmienna przechowująca obecny stan symulacji
  bool **_boolMap; //Wskaźnik na tablicę dwuwymiarową mapy
  int *_generationCount; //Wskaźnik na liczbę pokoleń
  int _importedgenerationCount; //Zmienna przechowująca wartość importowanej liczby pokoleń
  const int _MAP_SIZE_X; //stała przechowująca szerokość mapy
  const int _MAP_SIZE_Y; //stała przechowująca wysokość mapy
  const int _WINDOW_CORRECTION; //stała przechowująca przesunięcie mapy względem punktu (0,0) na ekranie
  std::string _log; //Zmienna przechowująca logi aplikacji
};

#endif //SIMULATIONSCENE_HPP
