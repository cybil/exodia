
#ifndef		ANIMATION_HPP__
# define	ANIMATION_HPP__

#include <SFML/Graphics.hpp>

class Animation
{
public:
  Animation();
  ~Animation();

  void			Initialize(float, float, int, int);
  void			Update(sf::RenderWindow &window);
  void			Draw(sf::RenderWindow &window);

  bool			getActive();
  void			setActive(bool);

  int			getCurrentFrame(int axis);
  void			setCurrentFrame(int axis, int value);

  float			getPosition(int axis);
  void			setPosition(int axis, float value);

  void		setImage(sf::Image &tempImage);

private:
  int			getFrameWidth();
  int			getFrameHeight();

private:
  sf::Sprite		spriteImage;
  unsigned int		currentFrameX;
  unsigned int		currentFrameY;
  float			x;
  float			y;
  float			frameCounter;
  int			switchFrame;
  int			amountOfFramesX;
  int			amountOfFramesY;

  bool			active;
  sf::Clock		clock;
};

#endif		// ! ANIMATION_HPP__
