
#include <iostream>
#include "SFML/Graphics/String.hpp"
#include "Player.hpp"

void		Player::affMessage(sf::RenderWindow &win, const std::string &str)
{
  sf::Font	myFont;

  if (!myFont.LoadFromFile(TTF))
    std::cerr << "Error during loading file " << TTF << std::endl;

  sf::String	Text(str, myFont, 50);
  Text.Move(250, 280);
  Text.SetColor(sf::Color(0, 0, 0));
  win.Draw(Text);
  _map->DrawLife(win);
  win.Display();
}

void		Player::endStage(sf::RenderWindow &win, const std::string &str)
{
  _map->DrawLife(win);
  affMessage(win, str);
  sleep(END_TIME);
  win.Close();
}

OBJECT		Player::checkCollision(float x, float y, float xo, float yo)
{
  // std::cerr << "x = " << (int)x << " // y = " << (int)y << std::endl;
  // std::cerr << "xo = " << xo << " // yo = " << yo << std::endl;
  // std::cerr << " ------------- x = " << (int)(x / SP_SIZE)  << " // y = " << (int)(y / SP_SIZE) << std::endl;
  // std::cerr << " ------------- xo = " << (int)(xo / SP_SIZE)  << " // yo = " << (int)(yo / SP_SIZE) << std::endl;

  int		xx = (int)(xo / SP_SIZE);
  int		yy = (int)(yo / SP_SIZE);

  if (_map->isWall(xx, yy))
    if (((x + SP_SIZE > xx * SP_SIZE) && (x + SP_SIZE < xx * SP_SIZE + SP_SIZE))
	|| ((x < xx * SP_SIZE + SP_SIZE) && (x > xx * SP_SIZE))
	|| ((y + SP_SIZE > yy * SP_SIZE) && (y + SP_SIZE < yy * SP_SIZE + SP_SIZE))
	|| ((y < yy * SP_SIZE + SP_SIZE) && (y > yy * SP_SIZE)))
      return WALL;
  return NONE;
}

OBJECT		Player::checkUnder(float x, float y, float xo, float yo)
{
  int		xx = (int)(xo / SP_SIZE);
  int		yy = (int)(yo / SP_SIZE);

  if (_map->isHole(xx, yy))
    if ((x > xx * SP_SIZE) && (x < xx * SP_SIZE + SP_SIZE))
      return HOLE;
  if (_map->isWall(xx, yy))
  {
    if ((x > xx * SP_SIZE) && (x < xx * SP_SIZE + SP_SIZE))
      return WALL;
  }
  return NONE;
}

void		Player::Initialize()
{
  x = 50;
  y = 50; //////////////////////////
  moveSpeed = 200;
  currentFrameX = currentFrameY = 0;
  playerAnimation.Initialize(x, y, 4, 4);
}

void		Player::LoadContent()
{
  if (!playerImage.LoadFromFile(MUMMY))
  {
    std::cerr << "Error loading file." << std::endl;
    return ;
  }
  playerAnimation.setImage(playerImage);
}

void		Player::fallHole(sf::RenderWindow &win, int xx, int yy)
{
  _map->setLife(_map->getLife() - 1);
  // x = xx * SP_SIZE;
  // y = yy * SP_SIZE;
  // Draw(win);
  affMessage(win, "You fell in a hole.");
  sleep(2);
  x = 500;
  y = 500;
}

void		Player::falling(float x, float y, sf::RenderWindow &win)
{
  OBJECT	obj;

  if ((obj = checkUnder(x + 15, y, x, y + SP_SIZE + (moveSpeed * win.GetFrameTime()))) == WALL)
  {
    _isFalling = false;
    if (_jumpStep == 0)
      _isJumping = false;
    return ;
  }
  if (obj == NONE)
    _isFalling = true;
}

void		Player::Update(sf::RenderWindow &win)
{
  playerAnimation.setActive(false);
  if (win.GetInput().IsKeyDown(sf::Key::Right))
  {
    if (checkCollision(x, y, x + SP_SIZE + (moveSpeed * win.GetFrameTime()), y + MARGE) <= HOLE
	&& (checkCollision(x, y, x + SP_SIZE + (moveSpeed * win.GetFrameTime()), y + SP_SIZE) <= HOLE))
      x += moveSpeed * win.GetFrameTime();
    if (checkUnder(x + 15, y, x + SP_SIZE, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) == HOLE)
      fallHole(win, x / SP_SIZE, y + SP_SIZE + (moveSpeed * win.GetFrameTime() / SP_SIZE));
    currentFrameY = 1;
    playerAnimation.setActive(true);
  }
  if (win.GetInput().IsKeyDown(sf::Key::Left))
  {
    if (checkCollision(x, y, x - (moveSpeed * win.GetFrameTime()), y + MARGE) <= HOLE
	&& (checkCollision(x, y, x - (moveSpeed * win.GetFrameTime()), y + SP_SIZE) <= HOLE))
      x -= moveSpeed * win.GetFrameTime();
    if (checkUnder(x + 35, y, x, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) == HOLE)
      fallHole(win, x / SP_SIZE, y + SP_SIZE + (moveSpeed * win.GetFrameTime() / SP_SIZE));
    currentFrameY = 0;
    playerAnimation.setActive(true);
  }
  if (win.GetInput().IsKeyDown(sf::Key::Space) && _isJumping == false)
  {
    if (checkCollision(x, y, x, y - (moveSpeed * win.GetFrameTime())) <= HOLE
    	&& (checkCollision(x, y, x + SP_SIZE, y - (moveSpeed * win.GetFrameTime())) <= HOLE))
    {
      _isJumping = true;
      _jumpStep = 15;
    }
    currentFrameY = 2;
    playerAnimation.setActive(true);
  }
  if (win.GetInput().IsKeyDown(sf::Key::Down))
  {
    if (checkCollision(x, y, x, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) <= HOLE
	&& (checkCollision(x, y, x + SP_SIZE, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) <= HOLE))
      y += moveSpeed * win.GetFrameTime();
    currentFrameY = 3;
    playerAnimation.setActive(true);
  }

  falling(x, y, win);
  if (_isJumping == true && _jumpStep > 0)
  {
    std::cerr << "win.GetFrameTime() = " << win.GetFrameTime() << std::endl;
    // y -= moveSpeed * win.GetFrameTime() + 10; // Essayer de garder plutot un modele comme ca...
    if (checkCollision(x, y, x, y - (moveSpeed * win.GetFrameTime())) <= HOLE
    	&& (checkCollision(x, y, x + SP_SIZE, y - (moveSpeed * win.GetFrameTime())) <= HOLE))
      y -= moveSpeed * win.GetFrameTime() * 3;
    _jumpStep--;
    _isFalling = false;
  }

  if (_isFalling == true)
  {
    if (checkCollision(x, y, x, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) <= HOLE
	&& (checkCollision(x, y, x + SP_SIZE, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) <= HOLE))
      y += moveSpeed * win.GetFrameTime() * 2;
      // y += 50;
    std::cout << "y = " << y << std::endl;
    // FAIRE : un system de mise a terre correct (!!), il faut que le y tombe sur des multiple de 50
  }

  // Ajustement de la position pour eviter des erreurs de collision
  if ((y <= 500 && y >= 497) || y >= 500)
    y = 499;

  if (win.GetInput().IsKeyDown(sf::Key::F))
    if (_map->isDalle((x + 6) / SP_SIZE, (y + 6) / SP_SIZE) == true)
      _map->activDalle();

  if (_map->getLife() == -1)
    this->endStage(win, LOST);

  if (_map->isDoor((x + 6) / SP_SIZE, (y + 6) / SP_SIZE) == true)
  {
      std::cerr << "You finish this stage. Good Game !" << std::endl;
      this->endStage(win, WIN);
  }

  playerAnimation.setPosition(1, x);
  playerAnimation.setPosition(2, y);
  playerAnimation.setCurrentFrame(2, currentFrameY);
  playerAnimation.Update(win);

}

void		Player::Draw(sf::RenderWindow &win)
{
  playerAnimation.Draw(win);
}


Player::Player(Map *gameMap)
{
  _map = gameMap;
  _isFalling = false;
  _isJumping = false;
  _jumpStep = 0;
}

Player::~Player()
{

}

