#include "../include/ImportScene.hpp"

ImportScene::ImportScene(Renderer *renderer, SimulationState& state, bool** &map, sf::Vector2i* mapSize, int *generationCount)
:_tmpMap(map)
{
  _renderer = renderer;
  _state = state;
  _aliveCellChar = '*';
  _deadCellChar = '-';
  _generationCount = generationCount;
  _mapSize = mapSize;
  *_mapSize = sf::Vector2i(0,0);
  _boolMap = nullptr;
}

ImportScene::~ImportScene()
{

}

SimulationState ImportScene::start()
{
  generateTexts();
  generateShape();
  while(_state == IMPORT)
  {
    handleEvents();
    _renderer->drawScene(this);
  }
  _tmpMap = _boolMap;
  return _state;
}


void ImportScene::handleEvents()
{
  sf::Event event;
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  std::string str = _texts[_inputTextIndex].getString();
  while(_renderer->getCurrentWindow()->pollEvent(event) && _state != END)
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
          _texts[_inputTextIndex].setString(str);
          _texts[_inputTextIndex].setPosition(windowSize.x/2-_texts[_inputTextIndex].getGlobalBounds().width/2,windowSize.y/2);
        }
      }
    }
    if (event.type == sf::Event::TextEntered)
    {
      if (str.size() < 21)
      {
        if (event.text.unicode > 31)
        {
            str += static_cast<char>(event.text.unicode);
            _texts[_inputTextIndex].setString(str);
            _texts[_inputTextIndex].setPosition(windowSize.x/2-_texts[_inputTextIndex].getGlobalBounds().width/2,windowSize.y/2);
        }
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      processClickEvent();

  }
}

void ImportScene::generateTexts()
{
  _texts.clear();
  sf::Vector2u windowSize(_renderer->getCurrentWindow()->getSize());
  sf::Text text;
  text.setFont(*_renderer->getCurrentFont());
  text.setCharacterSize(65);
  text.setString("Import");
  text.setColor(sf::Color::Green);
  text.setPosition(windowSize.x/2-text.getGlobalBounds().width/2,0);
  _texts.push_back(text);


  _inputTextIndex = 1;
  sf::Text text2;
  text2.setFont(*_renderer->getCurrentFont());
  text2.setCharacterSize(45);
  text2.setString("");
  text2.setColor(sf::Color::Magenta);
  text2.setPosition(windowSize.x/2-text2.getGlobalBounds().width,windowSize.y/2);
  _texts.push_back(text2);
}

void ImportScene::generateShape()
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

void ImportScene::processClickEvent()
{
  if(_renderer->isMouseOver(_shapes[0])) //rArrow
  {
    std::string str = _texts[_inputTextIndex].getString();
    validate(str);
  }
  else if(_renderer->isMouseOver(_shapes[1])) //lArrow
  {
    _state = MAIN_SCREEN;
  }
}

bool ImportScene::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void ImportScene::validate(std::string str)
{
  File f(str);
  std::string content = f.importFromFile();
  int genetaionIdx = content.find("generations");
  if(genetaionIdx > -1)
  {
    int endLineIdx = content.substr(genetaionIdx).find(",") < content.substr(genetaionIdx).find("}") ? content.substr(genetaionIdx).find(",") : content.substr(genetaionIdx).find("}");
    int startIdx = content.substr(genetaionIdx).find(":")+genetaionIdx+1;
    int endIdx = endLineIdx+genetaionIdx;
    std::string value = content.substr(startIdx, endIdx-startIdx);
    for(int i=0; i<value.size(); )
      if((value[i] == ' ') || (value[i] == '\t') || (value[i] == '\r') || (value[i] == '\n'))
        value.erase(i,1);
      else
        i++;
    if(is_number(value))
    {
      *_generationCount = std::stoi(value);
    }
    else
      throw INVALID_GENERATION_COUNT;
  }
  else
    throw INVALID_GENERATION_COUNT;

  int mapIdx = content.find("map");
  ListHandler list;
  if(mapIdx > -1)
  {
    int startIdx = content.substr(mapIdx).find("[")+mapIdx+1;
    int endIdx = content.substr(mapIdx).find("]")+mapIdx+1;
    std::string value = content.substr(startIdx, endIdx-startIdx);

    for(int i=0; i<value.size(); )
      if((value[i] == ' ') || (value[i] == '\t') || (value[i] == '\r') || (value[i] == '\n'))
        value.erase(i,1);
      else
        i++;


    while(value != "")
    {
        int endLineIdx = value.find(",") < value.find("]") ? value.find(",") : value.find("]");
        std::string tmp = value.substr(1, endLineIdx-2);

        int colCount = tmp.size();
        if(_mapSize->x == 0)
          _mapSize->x = colCount;
        else if(_mapSize->x != colCount)
          throw INVALID_COL_NUMBER;

        for(char c : tmp)
          if(c != _aliveCellChar && c != _deadCellChar)
            throw INVALID_MAP_CHAR;

        if(endLineIdx == value.find("]"))
          value = value.substr(endLineIdx+1);
        else
          value = value.substr(endLineIdx+1);

        list.addToList(tmp);
        _mapSize->y++;
    }
  }
  else
    throw INVALID_MAP;

    processValidMap(list);
}

void ImportScene::processValidMap(ListHandler &list)
{
  _boolMap = new bool*[_mapSize->x];
  for(int i=0; i<_mapSize->x; i++)
  {
    _boolMap[i] = new bool[_mapSize->y];
    int j=0;
    for(char c : list[i])
    {
      if(c == _aliveCellChar)
        _boolMap[i][j] = true;
      else
        _boolMap[i][j] = false;
      j++;
    }
  }
  _state = SIMULATION;
}
