#include "../include/MainScene.hpp"

MainScene::MainScene(Renderer *renderer, SimulationState& state)
{
  _renderer = renderer;
  _state = state;
}

MainScene::~MainScene()
{

}

SimulationState MainScene::start()
{
  generateTexts();
  while(_state == MAIN_SCREEN)
  {
    handleEvents();
    _renderer->drawScene(this);
  }
  return _state;
}

void MainScene::handleEvents()
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

void MainScene::generateTexts()
{
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  sf::Text text;
  text.setFont(*_renderer->getCurrentFont());
  text.setCharacterSize(65);
  text.setString("START");
  text.setColor(sf::Color::Green);
  text.setPosition(windowSize.x/2-text.getGlobalBounds().width/2,windowSize.y-250);
  _texts.push_back(text);


  std::string titleString = "GAME OF LIFE";
  for(int i=0; i<titleString.size(); i++)
  {
    sf::Text text2;
    text2.setFont(*_renderer->getCurrentFont());
    text2.setCharacterSize(65);
    text2.setString(titleString[i]);
    text2.setColor(sf::Color::Green);
    text2.setPosition(windowSize.x/2-text.getGlobalBounds().width/2+65*i-200,0);
    _texts.push_back(text2);
  }

  sf::Text text3;
  text3.setFont(*_renderer->getCurrentFont());
  text3.setCharacterSize(65);
  text3.setString("IMPORT FILE");
  text3.setColor(sf::Color::Green);
  text3.setPosition(windowSize.x/2-text3.getGlobalBounds().width/2,windowSize.y-150);
  _texts.push_back(text3);

}

void MainScene::proccessTextEvent()
{
  for(int i=0; i<_texts.size(); i++)
  {
    if(_renderer->isMouseOver(_texts[i]))
    {
      std::string s = _texts[i].getString();
      if(s == "START")
      {
        _state = CONFIGURATION;
        return;
      }
      if(s == "IMPORT FILE")
      {
        _state = IMPORT;
        return;
      }


      std::string titleString = "GAME OF LIFE";
      for(int j=0; j<titleString.size(); j++)
        if(titleString.find(s) >= 0)
          _texts[i].setColor(sf::Color::Red);

    }

  }
}
