#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <cstdio>
#include <istream>
#include <ostream>
#include "Scene.hpp"

/*
*  Klasa zajmująca się działaniami na plikach
*/

class File
{
public:
  File(std::string filename); //Konstruktor
  ~File(); //Destruktor
  void exportToFile(std::string content); //Metoda odpowiedzialna za eksportowanie podanej treści do pliku
  std::string importFromFile(); //Metoda odpowiedzialna za odczyt zawartości pliku
  friend std::istream & operator>>(std::istream &is, File &file); //Operator strumieniowy wejściowy
  friend std::ostream & operator<<(std::ostream &os, File &file); //Operator strumieniowy wyjściowy
private:
  std::string _filename; //Ciąg znaków przechowujący nazwę pliku
};

#endif //FILE_HPP
