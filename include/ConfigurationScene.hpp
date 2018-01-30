#ifndef CONFIGURATIONSCENE_HPP
#define CONFIGURATIONSCENE_HPP


#include "Scene.hpp"
#include "Renderer.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>

/*
* implementacja interfejsu Scene dla ekranu ustawiania wysokości i szerokości mapy
*/

class ConfigurationScene : public Scene
{
public:
  ConfigurationScene(Renderer *renderer, SimulationState& state); //Konstruktor
  SimulationState start() override; //Nadpisana metoda uruchamiająca pętlę sceny
  ~ConfigurationScene(); //Destruktor


private:
  void handleEvents() override; //Nadpisana metoda odpowiedzialna za przechwytywanie eventów
  void processClickEvent(); //Metoda obsługująca akcje działające po wybraniu przycisku myszy
  void generateTexts(); //Metoda odpowiedzialna za generowanie napisów
  void generateShape(); //Metoda odpowiedzialna za generowanie kształtów

  bool _isSetWidth; //Flaga określająca, czy jest wyświetlany ekran ustawiania szerokości mapy
  Renderer *_renderer; //Wskaźnik na obiekt Renderer
  SimulationState _state; //Zmienna przechowująca obecny stan symulacji
  int inputTextIndex; //Zmienna przechowująca indeks napisu, którego treść jest wpisywana przez użytkownika
};

#endif //CONFIGURATIONSCENE_HPP
