
#include <iostream>
#include "Animation.hpp"

int			Animation::getFrameWidth()
{
  return spriteImage.GetImage()->GetWidth() / amountOfFramesX;
}

int			Animation::getFrameHeight()
{
  return spriteImage.GetImage()->GetHeight() / amountOfFramesY;
}

bool			Animation::getActive()
{
  return active;
}

void			Animation::setActive(bool b)
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
    currentFrameY = value;
}

float			Animation::getPosition(int axis)
{
  if (axis == 1)
    return x;
  return y;
}

void			Animation::setPosition(int axis, float value)
{
  if (axis == 1)
    x = value;
  else
    y = value;
}

void			Animation::setImage(sf::Image &tempImage)
{
  spriteImage.SetImage(tempImage);
}

void			Animation::Initialize(float x, float y, int frameX, int frameY)
{
  frameCounter = 0;
  switchFrame = 1.0;
  this->x = x;
  this->y = y;
  this->amountOfFramesX = frameX;
  this->amountOfFramesY = frameY;
  this->active = false;
}

void			Animation::Update(sf::RenderWindow &win) /* unused win /!\ */
{
  if (active)
    frameCounter += clock.GetElapsedTime();
  else
    frameCounter = 0;

  if (frameCounter >= switchFrame)
  {
    frameCounter = 0;
    clock.Reset();
    currentFrameX += getFrameWidth();
    if (currentFrameX >= spriteImage.GetImage()->GetWidth())
      currentFrameX = 0;
  }
  spriteImage.SetSubRect(sf::IntRect(currentFrameX, currentFrameY * getFrameHeight(), currentFrameX + getFrameWidth(), currentFrameY * getFrameHeight() + getFrameHeight()));
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

