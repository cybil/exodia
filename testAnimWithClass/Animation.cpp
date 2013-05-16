
#include "Animation.hpp"

void			Animation::setImage(sf::Image tempImage)
{
  spriteImage.SetImage(tempImage);
}

int			Animation::getFrameWidth()
{
  return spriteImage.GetImage().GetWidth() / amountOfFramesX;
}

int			Animation::getFrameHeight()
{
  return spriteImage.GetImage().GetHeight() / amountOfFramesY;
}

bool			Animation::getActive()
{
  return active;
}

bool			Animation::setActive(bool b)
{
  active = b;
}

int			Animation::getCurrentFrame(int axis)
{
  if (axis == 1)
    return currentFrameX;
  return currentFrameY;
}

void			Animation::setCurrentFrame(int axis, int value)
{
  if (axis == 1)
    currentFrameX = value;
  else
    currentFrameY = value
}

int			Animation::getPosition(int axis)
{
  if (axis == 1)
    return x;
  return y;
}

void			Animation::setPosition(int axis, int value)
{
  if (axis == 1)
    x = value;
  else
    y = value;
}

void			Animation::Initialize(int x, int y, int frameX, int frameY, sf::Image tempImage)
{
  frameCounter = 0;
  switchFrame = 60;
  this->x = x;
  this->y = y;
  this->amountOfFramesX = frameX;
  this->amountOfFramesY = frameY;
  this->spriteImage.SetImage(tempImage);
  this->active = false;
}

void			Animation::Update(sf::RenderWindow &win)
{
  if (active)
    frameCounter += (int)win.GetFrameTime();
  else
    frameCounter = 0;

  if (frameCounter >= switchFrame)
  {
    frameCounter = 0;
    currentFrameX += getFrameWidth();
    if (currentFrameX >= spriteImage.GetImage().GetWidth())
      currentFrameX = 0;
  }
  spriteImage.SetSubRect(sf::IntRect(currentFrameX, currentFrameY * getFrameHeight(), currentFrameX + getFrameWidth(), currentFrameY + getFrameHeight()));
  spriteImage.SetPosition(x, y);
}

void			Animation::Draw(sf::RenderWindow &win)
{
  win.Draw(spriteImage);
}

Animation::Animation()
{

}

Animation::~Animation()
{

}

