
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

const int		JUMP_CONST = 8000;

enum OBJECT
{
  NONE = 0,
  HOLE,
  WALL,
  MONSTER
};

struct	t_dir
{
  float	x;
  float y;
};

class Player
{
public:
  Player(Map *);
  Player(const Player &);
  ~Player();

  void			Initialize();
  void			LoadContent();
  void			fallHole(sf::RenderWindow &, int, int);
  void			Update(sf::RenderWindow &);
  void			Draw(sf::RenderWindow &);

  Map			*getMap() const;
  t_dir			getDir() const;
  bool			isFalling() const;
  int			isJumping() const;
  int			getJumpStep() const;

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
  int			_isJumping;
  int			_jumpStep;
  t_dir			_direction;
  int			_jumpConst;
  bool			_canDoubleJump;
};

#endif		// ! PLAYER_HPP__
