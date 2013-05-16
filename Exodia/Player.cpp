
#include <iostream>
#include <fstream>
#include "Player.hpp"

using namespace sf;

bool		Player::move(std::pair<int, int> &coord)
{
  _coord = coord;
}

void		Player::initSprite()
{
  Sprite	*sp1 = new Sprite;
  Sprite	*sp2 = new Sprite;
  Sprite	*sp3 = new Sprite;
  Sprite	*sp4 = new Sprite;

  // Init sprite position for Player
  if (!this->_img.LoadFromFile("./Mummy.png"))
  {
    std::cerr << __PRETTY_FUNCTION__ << " : Erreur durant le chargement de l'image." << std::endl;
    return ;
  }
  // Left
  sp1->SetImage(this->_img);
  sp1->SetSubRect(IntRect(0, 0, 50, 50));
  sp1->SetPosition(55, 55);
  this->_spList.push_back(sp1);

  // Right
  sp2->SetImage(this->_img);
  sp2->SetSubRect(IntRect(0, 50, 50, 100));
  sp2->SetPosition(60, 60);
  this->_spList.push_back(sp2);

  // Up
  sp3->SetImage(this->_img);
  sp3->SetSubRect(IntRect(0, 100, 50, 150));
  sp3->SetPosition(70, 70);
  this->_spList.push_back(sp3);

  // Down
  sp4->SetImage(this->_img);
  sp4->SetSubRect(IntRect(0, 150, 50, 200));
  sp4->SetPosition(70, 70);
  this->_spList.push_back(sp4);
}

//
// Setters
//

void		Player::setCoord(std::pair<int, int> &coord)
{
  _coord = coord;
}

void		Player::setMap(std::map<int, std::string &> &map)
{
  _map = map;
}

void		Player::setLife(int life)
{
  _life = life;
}

//
// Getters
//

std::pair<int, int>	Player::getCoord() const
{
  return _coord;
}

std::map<int, std::string &>	Player::getMap() const
{
  return _map;
}

int		Player::getLife() const
{
  return _life;
}

//
// Constr / Destr
//

Player::Player(std::pair<int, int> &coord, int life, std::map<int, std::string &> &map)
{
  _coord = coord;
  _life = life;
  _map = map;
}

Player::Player(const Player &cpy)
{
  _coord = cpy.getCoord();
  _life = cpy.getLife();
  _map = cpy.getMap();
}

Player::~Player()
{
  std::cerr << "You are dead !" << std::endl;
}
