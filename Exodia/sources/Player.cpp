
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

  // std::cerr << "------------------------> xx = " << xx << std::endl;
  // std::cerr << "------------------------> yy = " << yy << std::endl;
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
  y = 499; //////////////////////////
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
  x = 50;
  y = 500;
}

void		Player::falling(float x, float y, sf::RenderWindow &win)
{
  OBJECT	obj;

  // std::cerr << "y = " << y + SP_SIZE + moveSpeed + 2 << std::endl; // (moveSpeed * win.GetFrameTime()
  // std::cerr << "x = " << x << std::endl;
  if ((obj = checkUnder(x + 15, y, x, y + SP_SIZE + 2)) == WALL)
  {
    std::cerr << "End fall." << std::endl;
    _isFalling = false;
    if (_jumpStep == 0)
    {
      _isJumping = 0;
      _canDoubleJump = false;
      _direction.y = 0.;
    }
    return ;
  }
  if (obj == NONE)
    _isFalling = true;
}

void		Player::Update(sf::RenderWindow &win)
{
  playerAnimation.setActive(false);

  // RIGHT
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

  // LEFT
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

  // JUMP
  if (win.GetInput().IsKeyDown(sf::Key::Space) && (_isJumping == 0 || _canDoubleJump == true))
  {
    if (checkCollision(x, y, x, y - (moveSpeed * win.GetFrameTime())) <= HOLE
    	&& (checkCollision(x, y, x + SP_SIZE, y - (moveSpeed * win.GetFrameTime())) <= HOLE))
    {
      if (_isJumping <= 2)
      {
	std::cerr << "Jump !" << std::endl;
	_isJumping += 1;
	_jumpConst = JUMP_CONST;
	_jumpStep = 9; // 8
      }
    }
    //currentFrameY = 2;
    playerAnimation.setActive(true);
  }

  // DOWN
  if (win.GetInput().IsKeyDown(sf::Key::Down))
  {
    if (checkCollision(x, y, x, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) <= HOLE
	&& (checkCollision(x, y, x + SP_SIZE, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) <= HOLE))
      y += moveSpeed * win.GetFrameTime();
    else
      _direction.y = 0.;
    currentFrameY = 3;
    playerAnimation.setActive(true);
  }

  if (win.GetInput().IsKeyDown(sf::Key::Return))
  {
    x = 50;
    y = 0;
  }
  std::cerr << "x = " << x << " - y = " << y << std::endl;

  falling(x, y, win);
  if (_isJumping >= 1 && _jumpStep > 0)
  {
    _jumpConst -= _jumpConst / 2 + JUMP_CONST / 600;
    // std::cerr << "win.GetFrameTime() = " << win.GetFrameTime() << std::endl;
    // y -= moveSpeed * win.GetFrameTime() + 10; // Essayer de garder plutot un modele comme ca...
    if (checkCollision(x, y, x, y - (moveSpeed * win.GetFrameTime())) <= HOLE
    	&& (checkCollision(x, y, x + SP_SIZE, y - (moveSpeed * win.GetFrameTime())) <= HOLE))
      y -= _jumpConst * win.GetFrameTime();
    _jumpStep--;
    _isFalling = false;
    std::cerr << "Step = " << _jumpStep << std::endl;
    // if (_jumpStep <= 2)
    //   _canDoubleJump = true;
  }

  if (_isFalling == true)
  {
    if (checkCollision(x, y, x, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) <= HOLE
	&& (checkCollision(x, y, x + SP_SIZE, y + SP_SIZE + (moveSpeed * win.GetFrameTime())) <= HOLE))
      y += _direction.y * win.GetFrameTime();
    else
      _direction.y = 0.;
      // y += 50;
    // std::cout << "y = " << y << std::endl;
    // FAIRE : un system de mise a terre correct (!!), il faut que le y tombe sur des multiple de 50
  }

  if (!_isJumping && !_isFalling)
  {
    std::cerr << "---------------------> x = " << x << " - y = " << y << std::endl;
    if ((y <= 500. && y >= 497.) || (y >= 500. && y <= 505.) || y >= 500.)
      y = 499;
    // if ((y <= 450 && y >= 447) || y >= 450)
    //   y = 449;
    // if ((y <= 400 && y >= 397) || y >= 400)
    //   y = 399;
    // if ((y <= 350 && y >= 347) || y >= 350)
    //   y = 349;
    // if ((y <= 300 && y >= 297) || y >= 300)
    //   y = 299;
    // if ((y <= 250 && y >= 247) || y >= 250)
    //   y = 249;
    // if ((y <= 200 && y >= 197) || y >= 200)
    //   y = 199;
    // if ((y <= 150 && y >= 147) || y >= 150)
    //   y = 149;
  }

  _direction.y += 20.;
  // Ajustement de la position pour eviter des erreurs de collision

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


Map			*Player::getMap() const
{
  return _map;
}

t_dir			Player::getDir() const
{
  return _direction;
}

bool			Player::isFalling() const
{
  return _isFalling;
}

int			Player::isJumping() const
{
  return _isJumping;
}

int			Player::getJumpStep() const
{
  return _jumpStep;
}

Player::Player(Map *gameMap)
{
  _direction.x = 0;
  _direction.y = 0;
  _map = gameMap;
  _isFalling = false;
  _isJumping = 0;
  _jumpStep = 0;
  _canDoubleJump = false;
}

Player::Player(const Player &cpy)
{
  _direction = cpy.getDir();
  _map = cpy.getMap();
  _isFalling = cpy.isFalling();
  _isJumping = cpy.isJumping();
  _jumpStep = cpy.getJumpStep();
  _canDoubleJump = false;
}

Player::~Player()
{

}

