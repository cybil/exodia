
#include <fstream>
#include <iostream>
#include "Map.hpp"

void					Map::DrawLife(sf::RenderWindow &win)
{
  int		x = 10;
  int		i = 0;

  win.Draw(_spriteTool);
  while (i < 3)
  {
    if (i >= _life)
    {
      _spriteHeart3.SetPosition(x, 605);
      win.Draw(_spriteHeart3);
    }
    else
    {
      _spriteHeart1.SetPosition(x, 605);
      win.Draw(_spriteHeart1);
    }
    x += 55;
    i++;
  }
}

void					Map::Draw(sf::RenderWindow &win)
{
  int		x = 0, y = 0;

  win.Draw(_spriteSand);
  _spriteTool.SetPosition(0, 600);
  for (int j = 0; _map[j].size(); ++j)
  {
    for (int i = 0; _map[j][i]; ++i)
    {
      if (_map[j][i] == '#')
      {
	_spriteWall.SetPosition(x, y);
	win.Draw(_spriteWall);
      }
      if (_map[j][i] == 'H')
      {
	_spriteHole.SetPosition(x, y);
	win.Draw(_spriteHole);
      }
      if (_map[j][i] == 'A')
      {
	if (_activ == true)
	{
	  _spriteDalleAct.SetPosition(x, y);
	  win.Draw(_spriteDalleAct);
	}
	else
	{
	  _spriteDalle.SetPosition(x, y);
	  win.Draw(_spriteDalle);
	}
      }
      if (_map[j][i] == 'D')
      {
	if (_activ == true)
	{
	  _spriteDoor.SetPosition(x, y);
	  win.Draw(_spriteDoor);
	}
	else
	{
	  _spriteWall.SetPosition(x, y);
	  win.Draw(_spriteWall);
	}
      }
      x += 50;
    }
    y += 50;
    x = 0;
  }
}

void					Map::activDalle()
{
  _activ = true;
}

//
// Initialize sprites
//

void					Map::initSprites()
{
  if (!_imgWall.LoadFromFile(WALL1))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteWall.SetImage(_imgWall);
  if (!_imgSand.LoadFromFile(BACKGRND))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteSand.SetImage(_imgSand);
  if (!_imgTool.LoadFromFile(BACKGRNDTOOL))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteTool.SetImage(_imgTool);
  if (!_imgDalle.LoadFromFile(DALLE1))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteDalle.SetImage(_imgDalle);
  if (!_imgDalleAct.LoadFromFile(DALLE2))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteDalleAct.SetImage(_imgDalleAct);
  if (!_imgDoor.LoadFromFile(DOOR1))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteDoor.SetImage(_imgDoor);
  if (!_imgHole.LoadFromFile(HOLE1))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteHole.SetImage(_imgHole);
  if (!_imgHeart1.LoadFromFile(HEART1))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteHeart1.SetImage(_imgHeart1);
  if (!_imgHeart2.LoadFromFile(HEART2))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteHeart2.SetImage(_imgHeart2);
  if (!_imgHeart3.LoadFromFile(HEART3))
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
  else
    _spriteHeart3.SetImage(_imgHeart3);
}

//
// Getters / Setters
//

void					Map::setMap(const std::string &mapName)
{
  std::ifstream file(mapName.c_str(), std::ios::in);

  if (file)
  {
    std::string	newline;
    for (int i = 0; getline(file, newline); i++)
      _map.insert(std::pair<int, std::string>(i, newline));
    file.close();
  }
  else
    std::cerr << "Fail to open the file." << std::endl;
}

const std::map<int, std::string>	&Map::getMap() const
{
  return _map;
}

const std::string			&Map::getLine(int line)
{
  return _map[line];
}

bool					Map::getActiv() const
{
  return _activ;
}

int					Map::getLife() const
{
  return _life;
}

void					Map::setLife(int life)
{
  _life = life;
}

bool					Map::isWall(int x, int y)
{
  if (_map[y][x] == '#'
      || (_map[y][x] == 'D' && _activ == false))
    return true;
  return false;
}

bool					Map::isDalle(int x, int y)
{
  if (_map[y][x] == 'A')
    return true;
  return false;
}

bool					Map::isDoor(int x, int y)
{
  if (_map[y][x] == 'D')
    return true;
  return false;
}

bool					Map::isHole(int x, int y)
{
  if (_map[y][x] == 'H')
    return true;
  return false;
}

//
// Constr / Destr
//

Map::Map(const std::string &mapName)
{
  setMap(mapName);
  _activ = false;
  _life = START_LIFE;
  initSprites();
}

Map::Map(const Map &cpy)
{
  _map = cpy.getMap();
  _activ = false;
  _life = cpy.getLife();
  initSprites();
}

Map::Map()
{
  _activ = false;
  _life = START_LIFE;
  initSprites();
}

Map::~Map()
{
  std::cerr << "Map deleted." << std::endl;
}
