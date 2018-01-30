#ifndef IMPOTRSCENE_HPP
#define IMPOTRSCENE_HPP

#include "Scene.hpp"
#include "Renderer.hpp"
#include "Enums.hpp"
#include "File.hpp"
#include "ListHandler.hpp"
#include <SFML/Graphics.hpp>

/*
* implementacja interfejsu Scene dla ekranu importu mapy
*/

class ImportScene : public Scene
{
public:
  ImportScene(Renderer *renderer, SimulationState& state, bool** &map, sf::Vector2i* mapSize, int *generationCount); //Konstruktor
  SimulationState start() override; //Nadpisana metoda uruchamiająca pętlę sceny
  ~ImportScene(); //Destruktor

private:
  void handleEvents() override; //Nadpisana metoda odpowiedzialna za przechwytywanie eventów
  void processClickEvent(); //Metoda obsługująca akcje działające po wybraniu przycisku myszy
  void generateTexts(); //Metoda odpowiedzialna za generowanie napisów
  void generateShape(); //Metoda odpowiedzialna za generowanie kształtów
  bool is_number(const std::string& s); //Metoda sprawdzająca, czy podany ciąg znaków jest liczbą
  void validate(std::string str); //Matoda przeprowadzająca walidację zawartości pliku importowanego
  void processValidMap(ListHandler& list); //Metoda przetwarzająca poprawny plik

  int _inputTextIndex; //Zmienna przechowująca indeks napisu, którego treść jest wpisywana przez użytkownika
  Renderer *_renderer; //Wskaźnik na obiekt Renderer
  SimulationState _state; //Zmienna przechowująca obecny stan symulacji
  int* _generationCount; //Wskaźnik na liczbę pokoleń
  bool **_boolMap; //Wskaźnik na tablicę dwuwymiarową mapy
  bool **&_tmpMap; //Zmienna przechowująca adres wskaźnika na tablicę dwuwymiarową mapy wprowadzonego w konstruktorze
  sf::Vector2i *_mapSize; //Wskaźnik na zmienną przechowującą rozmiar mapy
  char _aliveCellChar; //Zmienna przechowująca znak identyfikujący znak żywej komórki
  char _deadCellChar; //Zmienna przechowująca znak identyfikujący znak martwej komórki
};

#endif //IMPOTRSCENE_HPP
