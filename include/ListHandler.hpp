#ifndef LISTHANDLER_HPP
#define LISTHANDLER_HPP

#include <utility>
#include <string>

/*
* Klasa umożliwiająca działania na liście jednokierunkowej
*/

class ListHandler
{
public:
  ListHandler(): _head(nullptr), _listSize(0) { } //Konstruktor
  ~ListHandler(); //Destruktor
  int getSize(); //Metoda dostępowa zwracająca rozmiar listy
  void addToList(const std::string &element); //Metoda umożliwiająca dodawanie do listy
  std::string& operator[](const int &pos); //Operator indeksowania
  ListHandler& operator=(ListHandler other); //Operator przypisania

private:
  /*
  * Struktura przechowująca element listy jednokierunkowej
  */
  struct ListElement
  {
    std::string value; //Zmienna przechowująca wartość listy (ciąg znaków)
    ListElement* next; //Wskaźnik na następny element listy
  };

  ListElement* _head; //Wskaźnik na głowę listy
  int _listSize; //Zmienna przechowująca rozmiar listy
};

#endif //LISTHANDLER
