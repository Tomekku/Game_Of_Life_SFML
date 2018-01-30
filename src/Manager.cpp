#include "../include/Manager.hpp"

Manager::Manager(sf::RenderWindow *window, sf::Font *font)
{
    _renderer = new Renderer(window, font);
    _scene = nullptr;
    _state = MAIN_SCREEN;
}

Manager::~Manager()
{
  delete _renderer;
  delete _scene;
}

void Manager::start()
{
  bool **map = nullptr;
  int generationCount = 0;
  while(_state != END)
  {
    try
    {
      if(_scene != nullptr)
      {
        delete _scene;
        _scene = nullptr;
      }
      switch (_state)
      {
        case MAIN_SCREEN:
          _scene = new MainScene(_renderer, _state);
        break;
        case IMPORT:
          _scene = new ImportScene(_renderer, _state, map, &_mapSize, &generationCount);
        break;
        case CONFIGURATION:
          generationCount = 0;
          _scene = new ConfigurationScene(_renderer, _state);
        break;
        case CELL_SET:
          _scene = new CellSetScene(_renderer, _state, map, _mapSize.x, _mapSize.y);
        break;
        case SIMULATION:
          _scene = new SimulationScene(_renderer, _state, map, _mapSize, &generationCount);
        break;
        case RESULT:
          _scene = new ResultsScene(_renderer, _state, map, generationCount, _mapSize);
        break;
        case END:
          return;
        break;
        default:
          _state = END;
        break;
      }
      _state = _scene->start();
      if(_state == CELL_SET)
        _mapSize = _scene->getMapSize();
    }catch(ErrorCode e)
    {
      switch (e) {
        case FILE_NOT_EXIST:
          std::cout << "File does not exists" << '\n';
        break;
        case FILE_SAVE_FAIL:
          std::cout << "Could not be saved" << '\n';
        break;
        case INVALID_GENERATION_COUNT:
          std::cout << "Invalid number of generations" << '\n';
        break;
        case INVALID_MAP:
          std::cout << "Invalid map" << '\n';
        break;
        case INVALID_MAP_CHAR:
          std::cout << "Invalid char in map" << '\n';
        break;
        case INVALID_COL_NUMBER:
          std::cout << "Invalid number of column" << '\n';
        break;
        case ERROR:
          std::cout << "Something went wrong" << '\n';
        break;
        default:
        break;
      }
      _state = MAIN_SCREEN;
    } catch (...)
    {
      if(_scene != nullptr)
      {
        delete _scene;
        _scene = nullptr;
      }

      _state = MAIN_SCREEN;
    }
  }
  if(map != nullptr)
  {
    for(int i=0; i<_mapSize.x; i++)
      delete map[i];
    delete map;
  }

}
