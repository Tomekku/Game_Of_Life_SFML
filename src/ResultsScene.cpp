#include "../include/ResultsScene.hpp"



ResultsScene::ResultsScene(Renderer *renderer, SimulationState& state, bool **map, int &generationCount, sf::Vector2i& mapSize)
{
  _renderer = renderer;
  _state = state;
  _generationCount = generationCount;
  _map = map;
  _mapSize = mapSize;
}

ResultsScene::~ResultsScene()
{

}

SimulationState ResultsScene::start()
{
  generateTexts();
  while(_state == RESULT)
  {
    handleEvents();
    _renderer->drawScene(this);
  }
  return _state;
}

void ResultsScene::handleEvents()
{
  sf::Event event;
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  while(_renderer->getCurrentWindow()->pollEvent(event))
  {
    if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape))
        _state = END;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      proccessTextEvent();
  }
}

void ResultsScene::generateTexts()
{
  int offset = 140;
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  sf::Text text;
  text.setFont(*_renderer->getCurrentFont());
  text.setCharacterSize(65);
  text.setString("Return");
  text.setColor(sf::Color::Green);
  text.setPosition(windowSize.x/2-text.getGlobalBounds().width/2,windowSize.y-150);
  _texts.push_back(text);

  sf::Text text2;
  text2.setFont(*_renderer->getCurrentFont());
  text2.setCharacterSize(65);
  text2.setString("Results");
  text2.setColor(sf::Color::Green);
  text2.setPosition(windowSize.x/2-text2.getGlobalBounds().width/2,0);
  _texts.push_back(text2);

  int aliveCells = 0;
  for(int i=0; i<_mapSize.x*_mapSize.y; i++)
    aliveCells += _map[i%_mapSize.x][i/_mapSize.y];\
  std::string aliveCellsString = std::to_string(aliveCells);
  sf::Text text3;
  text3.setFont(*_renderer->getCurrentFont());
  text3.setCharacterSize(20);
  text3.setString("Number of alive cells: "+aliveCellsString);
  text3.setColor(sf::Color::Yellow);
  text3.setPosition(windowSize.x/2-text3.getGlobalBounds().width/2,offset);
  _texts.push_back(text3);

  sf::Text text4;
  std::string deadCellsString = std::to_string(_mapSize.x*_mapSize.y-aliveCells);
  text4.setFont(*_renderer->getCurrentFont());
  text4.setCharacterSize(20);
  text4.setString("Number of dead cells: "+deadCellsString);
  text4.setColor(sf::Color::Yellow);
  text4.setPosition(windowSize.x/2-text4.getGlobalBounds().width/2,offset*2);
  _texts.push_back(text4);

  sf::Text text5;
  std::string generationCountString = std::to_string(_generationCount);
  text5.setFont(*_renderer->getCurrentFont());
  text5.setCharacterSize(20);
  text5.setString("Number of generations: "+generationCountString);
  text5.setColor(sf::Color::Yellow);
  text5.setPosition(windowSize.x/2-text5.getGlobalBounds().width/2,offset*3);
  _texts.push_back(text5);

}

void ResultsScene::proccessTextEvent()
{
  for(int i=0; i<_texts.size(); i++)
  {
    if(_renderer->isMouseOver(_texts[i]))
    {
      std::string s = _texts[i].getString();
      if(s == "Return")
          _state = MAIN_SCREEN;

    }

  }
}
