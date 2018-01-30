#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Scene.hpp"
#include "SceneMap.hpp"

/*
* Klasa obsługująca rysowanie elementów na ekranie
*/

class Renderer
{
public:
  Renderer(sf::RenderWindow *window, sf::Font *font); //Konstruktor
  Renderer(Renderer &&r); //Konstruktor kopiujący
  ~Renderer(); //Destruktor
  void drawCells();
  void setCells(const std::vector<std::vector<bool>> &map);
  void drawScene(const Scene *scene); //Metoda odpowiedzialna za rysowanie sceny
  void drawScene(SceneMap *sceneMap); //Metoda odpowiedzialna za rysowanie sceny posiadajęcej mapę
  bool isEmptyMap(std::vector<std::vector<sf::RectangleShape>> map); //Metoda sprawdzająca, czy mapa jest pusta
  bool isMouseOver(sf::Text text); //Metoda obsługująca event najechania wskaźnikiem myszy na napis
  bool isMouseOver(sf::VertexArray shape); //Metoda obsługująca event najechania wskaźnikiem myszy na kształt
  bool isMouseOver(sf::RectangleShape rect); //Metoda obsługująca event najechania wskaźnikiem myszy na element mapy

  sf::Font* getCurrentFont() { return _font; } //Metoda dostępowa do pola sf::Font *_font
  sf::RenderWindow* getCurrentWindow() { return _window; } //Metoda dostępowa do pola sf::RenderWindow *_window

private:
  sf::RenderWindow *_window; //Wskaźnik na obiekt sf::RenderWindow przechowujący okno programu
  sf::Font *_font; //Wskaźnik na obiekt sf::Font przechowujący font
};
#endif //RENDERER_HPP
