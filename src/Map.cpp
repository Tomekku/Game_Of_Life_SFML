#include "../include/Map.hpp"

Map::Map(int sizeX, int sizeY, bool** boolMap)
: _MAP_SIZE_X(sizeX), _MAP_SIZE_Y(sizeY)
{
  _boolMap = boolMap;
}


inline bool Map::isLeft(int j)
{
  return (j-1 < 0);
}

inline bool Map::isRight(int j)
{
  return (j +1 >= _MAP_SIZE_Y);
}

inline bool Map::isUp(int i)
{
  return (i-1 < 0);
}

inline bool Map::isDown(int i)
{
  return (i+1 >= _MAP_SIZE_X);
}

bool Map::checkCells(std::vector<std::vector<sf::RectangleShape> > &map)
{
  bool end = true;
  bool newMap[_MAP_SIZE_X][_MAP_SIZE_Y];
  for(int i=0; i<_MAP_SIZE_X; i++)
  {
    for(int j=0; j<_MAP_SIZE_Y; j++)
    {
      bool cell = _boolMap[i][j];
      int neighbours[] = {
        (isLeft(j) || isUp(i)) ? 0 : (int)_boolMap[i-1][j-1],
        (isUp(i)) ? 0 : (int)_boolMap[i-1][j],
        (isRight(j) || isUp(i)) ? 0 : (int)_boolMap[i-1][j+1],
        (isLeft(j)) ? 0 : (int)_boolMap[i][j-1],
        (isRight(j)) ? 0 : (int)_boolMap[i][j+1],
        (isLeft(j) || isDown(i)) ? 0 : (int)_boolMap[i+1][j-1],
        (isDown(i)) ? 0 : (int)_boolMap[i+1][j],
        (isRight(j) || isDown(i)) ? 0 : (int)_boolMap[i+1][j+1],
      };

      int neighboursCount = 0;
      for (int iter = 0; iter < sizeof(neighbours)/sizeof(*neighbours); iter++)
        neighboursCount += neighbours[iter];


      newMap[i][j] = cell;

      if(cell && neighboursCount != 3 && neighboursCount != 2)
        newMap[i][j] = false;

      if(!cell && neighboursCount == 3)
        newMap[i][j] = true;

      if(newMap[i][j] != cell)
        end = false;

      if(newMap[i][j])
        map[i][j].setFillColor(sf::Color::Red);
      else
        map[i][j].setFillColor(sf::Color::Black);
    }
  }
  int aliveCellCount = 0;
  for(int i=0; i<_MAP_SIZE_X*_MAP_SIZE_Y; i++)
  {
    _boolMap[i%_MAP_SIZE_X][i/_MAP_SIZE_Y] = newMap[i%_MAP_SIZE_X][i/_MAP_SIZE_Y];
    aliveCellCount += _boolMap[i%_MAP_SIZE_X][i/_MAP_SIZE_Y];
  }

  return (aliveCellCount == 0 ? true : end);
}
