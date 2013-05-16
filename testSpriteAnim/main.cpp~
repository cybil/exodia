#include <iostream>
#include <SFML/Graphics.hpp>

const int sDown = 150;
const int sLeft = 0;
const int sRight = 50;
const int sUp = 100;


int		main()
{
  sf::RenderWindow	window(sf::VideoMode(800, 600, 32), "Exodia");

  sf::Image	tempImage;
  sf::Sprite	playerSprite;

  if (!tempImage.LoadFromFile("Mummy.png"))
  {
    std::cerr << "Error loading file." << std::endl;
    return 0;
  }
  playerSprite.SetImage(tempImage);

  float	velx = 0, vely = 0;
  float x = 10, y = 10, moveSpeed = 1.5;

  int	sourceX = 0;
  int	sourceY = sDown;


  while (window.IsOpened())
  {
    sf::Event	event;
    while (window.GetEvent(event))
    {
      if (event.Type == sf::Event::Closed || event.Key.Code == sf::Key::Escape)
	window.Close();
    }

    if (window.GetInput().IsKeyDown(sf::Key::Right))
    {
      sourceY = sRight;
      velx = moveSpeed;
    }
    else if (window.GetInput().IsKeyDown(sf::Key::Left))
    {
      sourceY = sLeft;
      velx = -moveSpeed;
    }
    else
      velx = 0;

    if (window.GetInput().IsKeyDown(sf::Key::Up))
    {
      sourceY = sUp;
      vely = -moveSpeed;
    }
    else if (window.GetInput().IsKeyDown(sf::Key::Down))
    {
      sourceY = sDown;
      vely = moveSpeed;
    }
    else
      vely = 0;

    x += velx;
    y += vely;

    if (velx != 0 || vely != 0)
      sourceX += tempImage.GetWidth() / 4;
    else
      sourceX = 0;

    if (sourceX == tempImage.GetWidth())
      sourceX = 0;

    window.Clear();
    playerSprite.SetSubRect(sf::IntRect(sourceX, sourceY, sourceX + tempImage.GetWidth() / 4, sourceY + tempImage.GetHeight() / 4));

    playerSprite.SetPosition(x, y);
    window.Draw(playerSprite);

    window.Display();

  }
  return (0);
}
