#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP

#include "Scene.hpp"
#include "Renderer.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>

/*
* implementacja interfejsu Scene dla ekranu głównego
*/

class MainScene : public Scene
{
public:
  MainScene(Renderer *renderer, SimulationState& state); //Konstruktor
  SimulationState start() override; //Nadpisana metoda uruchamiająca pętlę sceny
  ~MainScene(); //Destruktor

private:
  void handleEvents() override; //Nadpisana metoda odpowiedzialna za przechwytywanie eventów
  void proccessTextEvent(); //Metoda obsługująca akcje działające po wybraniu opcji w Menu głównym
  void generateTexts(); //Metoda odpowiedzialna za generowanie napisów

  Renderer *_renderer; //Wskaźnik na obiekt Renderer
  SimulationState _state; //Zmienna przechowująca obecny stan symulacji
};

#endif //MAINSCENE_HPP
