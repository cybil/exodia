
#ifndef		ANIMATION_HPP__
# define	ANIMATION_HPP__

#include <SFML/Graphics.hpp>

class Animation
{
public:
  Animation();
  ~Animation();

  void			Initialize(int, int, int, int, sf::Image);
  void			Update(sf::RenderWindow &window);
  void			Draw(sf::RenderWindow &window);

  bool			getActive();
  void			setActive(bool);

  int			getCurrentFrame(int axis);
  void			setCurrentFrame(int axis, int value);

  int			getPosition(int axis);
  void			setPosition(int axis, int value);

  
  void		setImage(sf::Image tempImage);

private:
  int			getFrameWidth();
  int			getFrameHeight();

private:
  sf::Sprite		spriteImage;
  int			currentFrameX;
  int			currentFrameY;
  float			x;
  float			y;
  int			frameCounter;
  int			switchFrame;
  int			amountOfFramesX;
  int			amountOfFramesY;

  bool			active;
};

#endif		// ! ANIMATION_HPP__
