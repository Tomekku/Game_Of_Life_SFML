#include "../include/ConfigurationScene.hpp"

ConfigurationScene::ConfigurationScene(Renderer *renderer, SimulationState& state)
{
  _renderer = renderer;
  _state = state;
  _isSetWidth = false;
}

ConfigurationScene::~ConfigurationScene()
{

}

SimulationState ConfigurationScene::start()
{
  while (_state == CONFIGURATION)
  {
    generateShape();
    if(_isSetWidth)
    {
      generateTexts();
      while(_state == CONFIGURATION && _isSetWidth)
      {
        handleEvents();
        _renderer->drawScene(this);
      }
    }
    else
    {
      generateTexts();
      while(_state == CONFIGURATION && !_isSetWidth)
      {
        handleEvents();
        _renderer->drawScene(this);
      }
    }
  }

  return _state;
}

void ConfigurationScene::handleEvents()
{
  sf::Event event;
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  std::string str = _texts[inputTextIndex].getString();
  while(_renderer->getCurrentWindow()->pollEvent(event))
  {
    if(event.type == sf::Event::Closed)
      _state = END;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      _state = END;
    if(event.type == sf::Event::KeyReleased)
    {
      if(event.key.code == sf::Keyboard::BackSpace)
      {
        if(!str.empty())
        {
          str = str.substr(0, str.size()-1);
          _texts[inputTextIndex].setString(str);
          _texts[inputTextIndex].setPosition(windowSize.x/2-_texts[inputTextIndex].getGlobalBounds().width/2,windowSize.y/2);
        }
      }
    }
    if (event.type == sf::Event::TextEntered)
    {
      if (str.size() < 2)
      {
        if (event.text.unicode > 47 && event.text.unicode < 58)
        {
            str += static_cast<char>(event.text.unicode);
            _texts[inputTextIndex].setString(str);
            _texts[inputTextIndex].setPosition(windowSize.x/2-_texts[inputTextIndex].getGlobalBounds().width/2,windowSize.y/2);
        }
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      processClickEvent();

  }
}

void ConfigurationScene::generateShape()
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

void ConfigurationScene::generateTexts()
{
  _texts.clear();
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  sf::Text text;
  text.setFont(*_renderer->getCurrentFont());
  text.setCharacterSize(65);
  if(_isSetWidth)
    text.setString("Set map height:");
  else
    text.setString("Set map width:");
  text.setColor(sf::Color::Green);
  text.setPosition(windowSize.x/2-text.getGlobalBounds().width/2,150);
  _texts.push_back(text);

  inputTextIndex = 1;
  sf::Text text2;
  text2.setFont(*_renderer->getCurrentFont());
  text2.setCharacterSize(65);
  text2.setString("");
  text2.setColor(sf::Color::Magenta);
  text2.setPosition(windowSize.x/2-text2.getGlobalBounds().width,windowSize.y/2);
  _texts.push_back(text2);
}

void ConfigurationScene::processClickEvent()
{
  if(_renderer->isMouseOver(_shapes[0])) //rArrow
  {
    std::string str = _texts[inputTextIndex].getString();
    if(!str.empty() && std::stoi(str) != 0)
    {
      if(!_isSetWidth)
      {
        _isSetWidth = true;
        mapSize.x = std::stoi(str);
      }
      else
      {
        _state = CELL_SET;
        mapSize.y = std::stoi(str);
      }
    }
  }
  else if(_renderer->isMouseOver(_shapes[1])) //lArrow
  {
    if(_isSetWidth)
      _isSetWidth = false;
    else
      _state = MAIN_SCREEN;
  }
}
