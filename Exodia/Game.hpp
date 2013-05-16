
#ifndef		GAME_HPP__
# define	GAME_HPP__

#include <map>
#include <string>
#include <list>
#include "Player.hpp"

class Game
{
public:
  Game(std::map<int, std::string &> &);
  Game(Game &);
  ~Game();

  void				addPlayer(Player &);
  std::list<Player>		&getPlayerList();
  std::map<int, std::string &>	&getMap();
  void				setMap(std::map<int, std::string &> &);

  void				launch();
  void				stop();
  void				loadMap(const std::string &);

private:
  std::list<Player>		_list;
  std::map<int, std::string &>	_map;
  MainWin			*_win;
};

#endif		// ! GAME_HPP__
