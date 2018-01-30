#ifndef ENUMS_HPP
#define ENUMS_HPP

/*
  Typ wyliczeniowy określający stan programu
*/
enum SimulationState
{
  MAIN_SCREEN, //Ekran startowy
  IMPORT, //Ekran importu plików
  CONFIGURATION, //Ekran konfiguracyjny
  CELL_SET, //Ekran ustawiania komórek
  SIMULATION, //Ekran synulacji
  RESULT, //Ekran wynków
  END //Stan określający zakończenie programu
};
/*
  Typ wyliczeniowy określający kod błędu
*/
enum ErrorCode
{
  FILE_NOT_EXIST, //Plik nie istnieje
  FILE_SAVE_FAIL, //Nie udało się zapisać pliku
  INVALID_GENERATION_COUNT, //Niepoprawna liczba pokoleń
  INVALID_MAP_CHAR, //Niepoprawny znak w mapie
  INVALID_MAP, //Niepoprawna mapa
  INVALID_COL_NUMBER, //Niepoprawna liczba kolumn
  INVALID_ROW_NUMBER, //Niepoprawna liczba wierszy
  ERROR //Inny błąd
};

#endif //ENUMS_HPP
