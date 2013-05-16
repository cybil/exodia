
#include "Player.hpp"

void		Player::Initialize()
{
  x = y = 10;
  moveSpeed = 200;
  currentFrameX = currentFrameY = 0;
}

void		Player::LoadContent()
{
  if (!playerImage.LoadFromFile("Mummy.png"))
    std::cerr << "Error loading file." << std::endl;
}

void		Player::Update(sf::RenderWindow &win)
{

}

Player::Player()
{

}

Player::~Player()
{

}

