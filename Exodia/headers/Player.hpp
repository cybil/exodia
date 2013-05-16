
#ifndef		PLAYER_HPP__
# define	PLAYER_HPP__

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Map.hpp"

const std::string	MUMMY = "img/human.png";
const std::string	LOST = "You have lost";
const std::string	WIN = "You finished the level";
const std::string	TTF = "misc/pieceOfEight.ttf";
const int		SP_SIZE = 50;
const int		MARGE = 4;
const int		END_TIME = 3;

enum OBJECT
{
  NONE = 0,
  HOLE,
  WALL,
  MONSTER
};

class Player
{
public:
  Player(Map *);
  ~Player();

  void			Initialize();
  void			LoadContent();
  void			fallHole(sf::RenderWindow &, int, int);
  void			Update(sf::RenderWindow &);
  void			Draw(sf::RenderWindow &);

protected:
  Animation		playerAnimation;

private:
  OBJECT		checkCollision(float, float, float, float);
  OBJECT		checkUnder(float, float, float, float);
  void			falling(float, float, sf::RenderWindow &);
  void			endStage(sf::RenderWindow &, const std::string &);
  void			affMessage(sf::RenderWindow &, const std::string &);

  Map			*_map;
  sf::Image		playerImage;
  float			x;
  float			y;
  int			currentFrameX;
  int			currentFrameY;
  float			moveSpeed;
  bool			_isFalling;
  bool			_isJumping;
  int			_jumpStep;
};

#endif		// ! PLAYER_HPP__
