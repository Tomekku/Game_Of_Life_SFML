#include "../include/CellSetScene.hpp"

CellSetScene::CellSetScene(Renderer *renderer, SimulationState& state, bool** &map, const int mapSizeX, const int mapSizeY)
:_MAP_SIZE_X(mapSizeX), _MAP_SIZE_Y(mapSizeY), _WINDOW_CORRECTION(100)
{
  _renderer = renderer;
  _state = state;
  _boolMap = new bool*[_MAP_SIZE_X];
  for(int i=0; i<_MAP_SIZE_X; i++)
  {
    _boolMap[i] = new bool[_MAP_SIZE_Y];
    for(int j=0; j<_MAP_SIZE_Y; j++)
      _boolMap[i][j] = false;
    std::vector<sf::RectangleShape> v;
    _map.push_back(v);
  }
  map = _boolMap;
}

CellSetScene::~CellSetScene()
{
}

SimulationState CellSetScene::start()
{
  generateTexts();
  generateMap();
  generateShape();
  while (_state == CELL_SET)
  {
      handleEvents();
      _renderer->drawScene(this);
  }

  return _state;
}

void CellSetScene::handleEvents()
{
  sf::Event event;
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());

  while(_renderer->getCurrentWindow()->pollEvent(event) && _state != END)
  {
    sf::Vector2i mousePositionOffset(sf::Mouse::getPosition(*_renderer->getCurrentWindow()));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      _state = END;
    if(event.type == sf::Event::Closed)
        _state = END;
    if(mousePositionOffset != mousePosition)
    {
      processMapEvents();
      mousePosition = mousePositionOffset;
      break;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      processClickEvent();

  }

}


void CellSetScene::generateShape()
{
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  sf::VertexArray rArrow(sf::TrianglesStrip, 6);
  int X_off = 20, Y_off = 60;
  int X_pos = windowSize.x-2*X_off, Y_pos = windowSize.y/2-Y_off;
  rArrow[0].position = sf::Vector2f(X_pos, Y_pos);
  rArrow[1].position = sf::Vector2f(X_pos+X_off,Y_pos);
  rArrow[2].position = sf::Vector2f(X_pos+X_off, Y_pos+Y_off);
  rArrow[3].position = sf::Vector2f(X_pos+2*X_off, Y_pos+Y_off);
  rArrow[4].position = sf::Vector2f(X_pos, Y_pos+2*Y_off);
  rArrow[5].position = sf::Vector2f(X_pos+X_off, Y_pos+2*Y_off);
  for(int i=0; i<6;i++)
    rArrow[i].color = sf::Color::Green;
  _shapes.push_back(rArrow);

  sf::VertexArray lArrow(sf::TrianglesStrip, 6);
  X_pos = 0;
  Y_pos = windowSize.y/2-Y_off;
  lArrow[0].position = sf::Vector2f(X_pos+2*X_off, Y_pos);
  lArrow[1].position = sf::Vector2f(X_pos+X_off,Y_pos);
  lArrow[2].position = sf::Vector2f(X_pos+X_off, Y_pos+Y_off);
  lArrow[3].position = sf::Vector2f(X_pos, Y_pos+Y_off);
  lArrow[4].position = sf::Vector2f(X_pos+2*X_off, Y_pos+2*Y_off);
  lArrow[5].position = sf::Vector2f(X_pos+X_off, Y_pos+2*Y_off);
  for(int i=0; i<6;i++)
    lArrow[i].color = sf::Color::Green;
  _shapes.push_back(lArrow);
}

void CellSetScene::generateTexts()
{
  _texts.clear();
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  sf::Text text;
  text.setFont(*_renderer->getCurrentFont());
  text.setCharacterSize(65);
  text.setString("Set all cells:");
  text.setColor(sf::Color::Green);
  text.setPosition(windowSize.x/2-text.getGlobalBounds().width/2,0);
  _texts.push_back(text);
}

void CellSetScene::processMapEvents()
{
  for(int i=0; i<_MAP_SIZE_X; i++)
  {
    for(int j=0; j<_MAP_SIZE_Y; j++)
    {
      if(_renderer->isMouseOver(_map[i][j]))
        _map[i][j].setOutlineColor(sf::Color::Green);
      else
        _map[i][j].setOutlineColor(sf::Color::White);
    }
  }
}

void CellSetScene::toggleCell(int i, int j)
{
  if(!_boolMap[i][j])
  {
    _map[i][j].setFillColor(sf::Color::Red);
    _boolMap[i][j] = true;
  }
  else
  {
    _map[i][j].setFillColor(sf::Color::Black);
    _boolMap[i][j] = false;
  }
}

void CellSetScene::processClickEvent()
{
  if(_renderer->isMouseOver(_shapes[0]))
    _state = SIMULATION;
  if(_renderer->isMouseOver(_shapes[1]))
    _state = CONFIGURATION;

  for(int i=0; i<_MAP_SIZE_X; i++)
    for(int j=0; j<_MAP_SIZE_Y; j++)
      if(_renderer->isMouseOver(_map[i][j]) )
        toggleCell(i, j);

}

bool** CellSetScene::exportMap()
{
  return _boolMap;
}

void CellSetScene::generateMap()
{
  int rectSide = getRectSide();
  for(int i=0; i<_MAP_SIZE_X; i++)
  {
    for(int j=0; j<_MAP_SIZE_Y; j++)
    {
      sf::RectangleShape rect;
      rect.setPosition(sf::Vector2f(i*rectSide+_WINDOW_CORRECTION, j*rectSide+_WINDOW_CORRECTION));
      rect.setSize(sf::Vector2f(rectSide,rectSide));
      rect.setFillColor(sf::Color::Black);
      rect.setOutlineColor(sf::Color::White);
      rect.setOutlineThickness(1);
      _map[i].push_back(rect);
    }
  }
}

int CellSetScene::getRectSide()
{
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  int sideOnY = (windowSize.y-2*_WINDOW_CORRECTION)/_MAP_SIZE_Y;
  int sideOnX = (windowSize.x-2*_WINDOW_CORRECTION)/_MAP_SIZE_X;
  return  sideOnY < sideOnX ? sideOnY : sideOnX;
}
