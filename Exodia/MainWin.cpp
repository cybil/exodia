
#include <fstream>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

#include "MainWin.hpp"

using namespace sf;

const int WALL_SIZE = 50;

void		MainWin::checkFall()
{
  float ElapsedTime = _app.GetFrameTime();

  if (_actSp.GetPosition().y + _actSp.GetSize().y < _app.GetHeight()
      && _map[(_actSp.GetPosition().y + WALL_SIZE + 2) / WALL_SIZE][(_actSp.GetPosition().x) / WALL_SIZE] == ' ')
  {
    while (_map[(_actSp.GetPosition().y + WALL_SIZE + 2) / WALL_SIZE][(_actSp.GetPosition().x) / WALL_SIZE] == ' ')
    {
      _spList[3]->SetPosition(_actSp.GetPosition());
      _spList[3]->Move(0, 100 * ElapsedTime);
      _actSp = *(_spList[3]);
    }
  }
}

void		MainWin::moveSprite()
{
  // Récupération du temps écoulé
  float ElapsedTime = this->_app.GetFrameTime();

  std::cout << "x = " << _actSp.GetPosition().x << " // y = " << _actSp.GetPosition().y << std::endl;
  std::cout << "CASE = [" << (int)_actSp.GetPosition().y / 50 << "][" << (int)_actSp.GetPosition().x / 50 << "]" << std::endl;

  // On déplace le sprite
  if (this->_app.GetInput().IsKeyDown(sf::Key::Left)
      && _actSp.GetPosition().x > 0
      && _map[(_actSp.GetPosition().y + 2) / WALL_SIZE][(_actSp.GetPosition().x - 2) / WALL_SIZE] != '#')
  {
    _spList[0]->SetPosition(_actSp.GetPosition());
    _spList[0]->Move(-100 * ElapsedTime, 0);
    _actSp = *(_spList[0]);
    this->checkFall();
  }
  if (_app.GetInput().IsKeyDown(sf::Key::Right)
      && _actSp.GetPosition().x + _actSp.GetSize().x < _app.GetWidth()
      && _map[(_actSp.GetPosition().y + 2) / WALL_SIZE][(_actSp.GetPosition().x + 2 + WALL_SIZE) / WALL_SIZE] != '#')
  {
    _spList[1]->SetPosition(_actSp.GetPosition());
    _spList[1]->Move(100 * ElapsedTime, 0);
    _actSp = *(_spList[1]);
    this->checkFall();
  }
  if (_app.GetInput().IsKeyDown(sf::Key::Up)
      && _actSp.GetPosition().y > 0
      && _map[(_actSp.GetPosition().y - 2) / WALL_SIZE][(_actSp.GetPosition().x) / WALL_SIZE] != '#')
  {
    _spList[2]->SetPosition(_actSp.GetPosition());
    _spList[2]->Move(0, -100 * ElapsedTime);
    _actSp = *(_spList[2]);
    this->checkFall();
  }
  if (_app.GetInput().IsKeyDown(sf::Key::Down)
      && _actSp.GetPosition().y + _actSp.GetSize().y < _app.GetHeight()
      && _map[(_actSp.GetPosition().y + WALL_SIZE + 2) / WALL_SIZE][(_actSp.GetPosition().x) / WALL_SIZE] != '#')
  {
    _spList[3]->SetPosition(_actSp.GetPosition());
    _spList[3]->Move(0, 100 * ElapsedTime);
    _actSp = *(_spList[3]);
    this->checkFall();
  }

  // A PERFECTIONNER LOL
  if (_app.GetInput().IsKeyDown(sf::Key::Space)
      && _actSp.GetPosition().y > 0
      && _map[(_actSp.GetPosition().y - 2) / WALL_SIZE][(_actSp.GetPosition().x) / WALL_SIZE] != '#')
  {
    _spList[2]->SetPosition(_actSp.GetPosition());
    _spList[2]->Move(0, -450 * ElapsedTime);
    _actSp = *(_spList[2]);
  }
}

void		MainWin::mainLoop()
{
  _actSp = *(this->_spList[0]);
  while (this->_app.IsOpened())
  {
    Event event;


    while (this->_app.GetEvent(event))
    {
      if (event.Type == Event::Closed)
  	this->_app.Close();
      if (event.Type == Event::KeyPressed)
  	if (event.Key.Code == Key::Escape)
  	  this->_app.Close();
    }

    this->moveSprite();

    if (event.Type == Event::KeyReleased)
      this->checkFall();
      // if (event.Type == Event::KeyReleased)
      // && event.Key.Code == Key::Space)

    // On tourne le sprite touches + et -
    // if (this->_app.GetInput().IsKeyDown(sf::Key::Add))
    //   this->_spList.front()->Rotate(-100 * ElapsedTime);
    // if (this->_app.GetInput().IsKeyDown(sf::Key::Subtract))
    //   this->_spList.front()->Rotate( 100 * ElapsedTime);

    this->_app.Clear();
    this->displayMap();
    this->display();
    this->_app.Display();
  }
}

void		MainWin::display()
{
  this->_app.Draw(this->_actSp);
}

void		MainWin::initSprite()
{
  Sprite	*sp1 = new Sprite;
  Sprite	*sp2 = new Sprite;
  Sprite	*sp3 = new Sprite;
  Sprite	*sp4 = new Sprite;

  // Init sprite position for Player
  if (!this->_img.LoadFromFile("./Mummy.png"))
  {
    std::cerr << "Erreur durant le chargement de l'image." << std::endl;
    return ;
  }
  // Left
  sp1->SetImage(this->_img);
  sp1->SetSubRect(IntRect(0, 0, 50, 50));
  sp1->SetPosition(55, 55);
  this->_spList.push_back(sp1);

  // Right
  sp2->SetImage(this->_img);
  sp2->SetSubRect(IntRect(0, 50, 50, 100));
  sp2->SetPosition(60, 60);
  this->_spList.push_back(sp2);

  // Up
  sp3->SetImage(this->_img);
  sp3->SetSubRect(IntRect(0, 100, 50, 150));
  sp3->SetPosition(70, 70);
  this->_spList.push_back(sp3);

  // Down
  sp4->SetImage(this->_img);
  sp4->SetSubRect(IntRect(0, 150, 50, 200));
  sp4->SetPosition(70, 70);
  this->_spList.push_back(sp4);
}

void		MainWin::displayMap()
{
  int		x = 0, y = 0;

  for (int j = 0; _map[j].size(); ++j)
  {
    for (int i = 0; _map[j][i]; ++i)
    {
      if (_map[j][i] == '#')
      {
	_border.SetPosition(x, y);
	_app.Draw(_border);
	x += 50;
      }
      else
	x += 50;
    }
    y += 50;
    x = 0;
  }
}

void		MainWin::loadMap(const std::string &gameMap)
{
  std::ifstream file(gameMap.c_str(), std::ios::in);

  if (file)
  {
    if (!_borderImg.LoadFromFile("wall.jpg"))
    {
      std::cerr << "Erreur durant le chargement de l'image." << std::endl;
      return ;
    }
    std::string	newline;

    _border.SetImage(_borderImg);
    for (int i = 0; getline(file, newline); i++)
    {
      _map.insert(std::pair<int, std::string>(i, newline));
    }
    file.close();
  }
  else
    std::cerr << "Fail to open the file." << std::endl;
}

MainWin::MainWin()
{
  this->_app.Create(VideoMode(800, 600, 32), "Coucou");
}

MainWin::~MainWin()
{
}
