#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <SFML/Graphics.hpp>

/*
* Klasa przetwarzająca mapę symulacji
*/

class Map
{
public:
  Map(int sizeX, int sizeY, bool** boolMap); //Konstruktor
  bool checkCells(std::vector<std::vector<sf::RectangleShape> > &map); //Metoda odpowiedzialna za algorytm generowania nowej mapy

private:
  inline bool isLeft(int j); //Metoda sprawdzająca, czy komórka po lewej stronie indeksu istnieje
  inline bool isRight(int j); //Metoda sprawdzająca, czy komórka po prawej stronie indeksu istnieje
  inline bool isUp(int i); //Metoda sprawdzająca, czy komórka u góry od indeksu istnieje
  inline bool isDown(int i); //Metoda sprawdzająca, czy komórka na dole od indeksu istnieje

  const int _MAP_SIZE_X; //stała przechowująca szerokość mapy
  const int _MAP_SIZE_Y; //stała przechowująca wysokość mapy
  bool **_boolMap; //Wskaźnik na tablicę dwuwymiarową mapy
};

#endif //MAP_HPP
