#include "../include/SimulationScene.hpp"


SimulationScene::SimulationScene(Renderer *renderer, SimulationState& state, bool** map, sf::Vector2i& mapSize, int *generationCount)
:_MAP_SIZE_X(mapSize.x), _MAP_SIZE_Y(mapSize.y), _WINDOW_CORRECTION(100)
{
  _boolMap = map;
  _renderer = renderer;
  _state = state;
  _generationCount = generationCount;
  _importedgenerationCount = (*generationCount);
  for(int i=0; i<_MAP_SIZE_X; i++)
  {
    std::vector<sf::RectangleShape> v;
    _map.push_back(v);
  }
  _log = "";
}

SimulationState SimulationScene::start()
{
  generateMap();
  generateTexts();
  generateShape();

  std::string logfilename = "LOG.txt";
  Map m(_MAP_SIZE_X, _MAP_SIZE_Y, _boolMap);
  bool end = false;
  bool generationCountSet = (*_generationCount) != 0 ? true : false;
  for(int i=0;_state == SIMULATION && !end && (*_generationCount) >= 0;i++)
  {
    if(i % 10 == 0)
    {
      end = m.checkCells(_map);
      if(generationCountSet)
        (*_generationCount)--;
      else
        (*_generationCount)++;
      logCurrentState();
    }
    handleEvents();
    _renderer->drawScene(this);
  }
  _renderer->drawScene(this);
  File f(logfilename);
  f.exportToFile(_log);

  if(generationCountSet)
  {
    (*_generationCount) = _importedgenerationCount;
    _state = RESULT;
  }

  return _state;

}

SimulationScene::~SimulationScene()
{

}

void SimulationScene::generateMap()
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

void SimulationScene::generateTexts()
{
  _texts.clear();
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  sf::Text text;
  text.setFont(*_renderer->getCurrentFont());
  text.setCharacterSize(65);
  text.setString("Simulation");
  text.setColor(sf::Color::Green);
  text.setPosition(windowSize.x/2-text.getGlobalBounds().width/2,0);
  _texts.push_back(text);

  sf::Text textButton;
  textButton.setFont(*_renderer->getCurrentFont());
  textButton.setCharacterSize(35);
  textButton.setString("STOP");
  textButton.setColor(sf::Color::Black);
  textButton.setPosition(windowSize.x-150, windowSize.y-70);
  _texts.push_back(textButton);
}

void SimulationScene::generateShape()
{
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  sf::VertexArray stopButton(sf::Quads, 4);
  int X_off = 180, Y_off = 60;
  int X_pos = windowSize.x-X_off-10, Y_pos = windowSize.y-Y_off-10;
  stopButton[0].position = sf::Vector2f(X_pos, Y_pos);
  stopButton[1].position = sf::Vector2f(X_pos+X_off,Y_pos);
  stopButton[2].position = sf::Vector2f(X_pos+X_off, Y_pos+Y_off);
  stopButton[3].position = sf::Vector2f(X_pos, Y_pos+Y_off);
  for(int i=0; i<4;i++)
    stopButton[i].color = sf::Color::Yellow;
  _shapes.push_back(stopButton);

}

void SimulationScene::handleEvents()
{
  sf::Event event;
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());

  while(_renderer->getCurrentWindow()->pollEvent(event) && _state != END)
  {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      _state = END;
    if(event.type == sf::Event::Closed)
      _state = END;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      processClickEvent();
  }

}

void SimulationScene::processClickEvent()
{
  if(_renderer->isMouseOver(_shapes[0]) || _renderer->isMouseOver(_texts[1]))
    _state = RESULT;
}

int SimulationScene::getRectSide()
{
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  int sideOnY = (windowSize.y-2*_WINDOW_CORRECTION)/_MAP_SIZE_Y;
  int sideOnX = (windowSize.x-2*_WINDOW_CORRECTION)/_MAP_SIZE_X;
  return  sideOnY < sideOnX ? sideOnY : sideOnX;
}

void SimulationScene::logCurrentState()
{
  int aliveCells = 0;
  for(int i=0; i<_MAP_SIZE_X*_MAP_SIZE_Y; i++)
    aliveCells += _boolMap[i%_MAP_SIZE_X][i/_MAP_SIZE_Y];
  std::string aliveCellsString = std::to_string(aliveCells);
  std::string deadCellsString = std::to_string(_MAP_SIZE_X*_MAP_SIZE_Y-aliveCells);
  std::string generationCountString = std::to_string((*_generationCount));
  _log += "Alive cells: "+aliveCellsString+"; Dead Cells: "+deadCellsString+"; Generation: "+generationCountString+"\n";
}
