#ifndef RESULTSSCENE_HPP
#define RESULTSSCENE_HPP


#include "Scene.hpp"
#include "Renderer.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>


/*
* implementacja interfejsu Scene dla ekranu wyświetlającego podsumowanie symulacji
*/

class ResultsScene : public Scene
{
public:
  ResultsScene(Renderer *renderer, SimulationState& state, bool **map, int &generationCount, sf::Vector2i& mapSize); //Konstruktor
  SimulationState start() override; //Nadpisana metoda uruchamiająca pętlę sceny
  ~ResultsScene(); //Destruktor

private:
  void handleEvents() override; //Nadpisana metoda odpowiedzialna za przechwytywanie eventów
  void proccessTextEvent(); //Metoda obsługująca akcje działające po wybraniu opcji w oknie podsumowania
  void generateTexts(); //Metoda odpowiedzialna za generowanie napisów


  Renderer *_renderer; //Wskaźnik na obiekt Renderer
  SimulationState _state; //Zmienna przechowująca obecny stan symulacji
  int _generationCount; //Zmienna przechowująca liczbę pokoleń
  bool **_map; //Wskaźnik na tablicę dwuwymiarową mapy
  sf::Vector2i _mapSize; //Zmienna przechowująca rozmiar mapy
};


#endif //RESULTSSCENE_HPP
