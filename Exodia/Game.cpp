
#include <iostream>
#include "Game.hpp"

void				Game::launch()
{
  std::cerr << "Game launched" << std::endl;
}

void				Game::stop()
{
  std::cerr << "Game stopped" << std::endl;
}

void		Game::loadMap(const std::string &gameMap)
{
  std::ifstream file(gameMap.c_str(), std::ios::in);

  if (file)
  {
    std::string	newline;
    for (int i = 0; getline(file, newline); i++)
      _map.insert(std::pair<int, std::string>(i, newline));
    file.close();
  }
  else
    std::cerr << "Fail to open the file." << std::endl;
}

//
// Setters
//

void				Game::setMap(std::map<int, std::string &> &map)
{
  _map = map;
}

//
// Getters
//

std::list<Player>		&Game::getPlayerList()
{
  return _list;
}

std::map<int, std::string &>	&Game::getMap()
{
  return _map;
}

//
// Constr / Destr
//

Game::Game(std::map<int, std::string &> &map)
{
  _win = new MainWin();
//  _win->initSprite();
  _map = map;
}

Game::Game(Game &cpy)
{
  _list = cpy.getPlayerList();
  _map = cpy.getMap();
}

Game::~Game()
{
  std::cerr << "This game is ended." << std::endl;
  delete _win;
}
