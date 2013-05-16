
#ifndef		PLAYER_HPP__
# define	PLAYER_HPP__

#include <vector>
#include <SFML/Graphics.hpp>
#include <utility>
#include <map>
#include <string>

class Player
{
public:
  Player(std::pair<int, int> &, int, std::map<int, std::string &> &);
  Player(const Player &);
  ~Player();


  bool				move(std::pair<int, int> &);
  void				initSprite();

  void				setCoord(std::pair<int, int> &);
  void				setLife(int);
  void				setMap(std::map<int, std::string &> &);
  std::pair<int, int>		getCoord() const;
  int				getLife() const;
  std::map<int, std::string &>	getMap() const;

private:
  std::pair<int, int>		_coord;
  int				_life;
  std::map<int, std::string &>	_map;
  std::vector<sf::Sprite *>	_spList;
  sf::Image			_img;
};

#endif		// ! PLAYER_HPP__
