#include "../include/ListHandler.hpp"


ListHandler::~ListHandler()
{
  ListElement *p;
	while(_head)
	{
		p=_head->next;
		delete _head;
		_head = p;
	}
}

int ListHandler::getSize()
{
  return _listSize;
}

void ListHandler::addToList(const std::string &element)
{
  if(_head)
  {
    ListElement* tmp = _head;
    while(tmp->next)
      tmp = tmp->next;
    tmp->next = new ListElement{element, nullptr};
  }
  else
    _head = new ListElement{element, nullptr};
  _listSize++;
}

ListHandler& ListHandler::operator=(ListHandler other)
{
  ListElement *p;
	while(_head)
	{
		p=_head->next;
		delete _head;
		_head = p;
	}

  _listSize = other._listSize;
  _head = nullptr;
  for (int i = 0; i < _listSize; i++)
      this->addToList(other[i]);
  return *this;
}

std::string& ListHandler::operator[](const int &pos)
{

  ListElement* tmp = _head;
  for(int i=0; i<pos; i++)
    tmp = tmp->next;
  return tmp->value;

}
