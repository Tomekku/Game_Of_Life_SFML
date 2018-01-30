#include "../include/Renderer.hpp"

Renderer::Renderer(sf::RenderWindow *window, sf::Font *font)
{
  _window = window;
  _font = font;
}

Renderer::Renderer(Renderer &&r)
{
  _window = r._window;
  _font = r._font;
}

Renderer::~Renderer()
{

}

void Renderer::drawScene(const Scene *scene)
{
  _window->clear(sf::Color(46, 53, 42 ,255));
  if(!scene->getShapes().empty())
  {
    for(sf::VertexArray &v : scene->getShapes())
    {
      _window->draw(v);
    }
  }
  if(!scene->getTexts().empty())
  {
    for(sf::Text &t : scene->getTexts())
    {
      _window->draw(t);
    }
  }
  _window->display();
}

void Renderer::drawScene(SceneMap *sceneMap)
{
  _window->clear(sf::Color(46, 53, 42 ,255));
  if(!sceneMap->getShapes().empty())
  {
    for(sf::VertexArray &v : sceneMap->getShapes())
    {
      _window->draw(v);
    }
  }
  
  if(!sceneMap->getTexts().empty())
  {
    for(sf::Text &t : sceneMap->getTexts())
    {
      _window->draw(t);
    }
  }

  std::vector<std::vector<sf::RectangleShape>> map = sceneMap->getMap();

  if(!isEmptyMap(map))
  {
    for(int x=0; x<map.size(); x++)
    {
      for(int y=0; y<map[x].size(); y++)
      {
        _window->draw(map[x][y]);
      }
    }
  }
  _window->display();
}

bool Renderer::isEmptyMap(std::vector<std::vector<sf::RectangleShape>> map)
{
  if(map.empty() || map[0].empty())
    return true;
  return false;
}

bool Renderer::isMouseOver(sf::Text text)
{
  sf::Vector2f mousePosition(sf::Mouse::getPosition(*_window));
  if(text.getGlobalBounds().contains(mousePosition))
    return true;
  return false;
}

bool Renderer::isMouseOver(sf::VertexArray shape)
{
  sf::Vector2f mousePosition(sf::Mouse::getPosition(*_window));
  if(shape.getBounds().contains(mousePosition))
    return true;
  return false;
}

bool Renderer::isMouseOver(sf::RectangleShape rect)
{
  sf::Vector2f mousePosition(sf::Mouse::getPosition(*_window));
  if(rect.getGlobalBounds().contains(mousePosition))
    return true;
  return false;
}
