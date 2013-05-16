
#ifndef		PLAYER_HPP__
# define	PLAYER_HPP__

#include <SFML/Grpahics.hpp>
#include "Animation.hpp"

class Player
{
public:
  Player();
  ~Player();

  void		Initialize();
  void		LoadContent();
  void		Update(sf::RenderWindow &win);
  void		Draw(sf::RenderWindow &win);

protected:
  Animation		playerAnimation;

private:
  sf::Image		playerImage;
  float			x;
  float			y;
  int			currentFrameX;
  int			currentFrameY;
  float			moveSpeed;

};

#endif		// ! PLAYER_HPP__
