#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Map.hpp"

const int	sDown = 0;
const int	sRight = 0;
const int	sLeft = 0;
const int	sUp = 0;

const int	HEIGHT = 800;
const int	WIDTH = 660;
const int	BIT_MODE = 64;

int		main(int ac, char **av)
{
  sf::RenderWindow	window(sf::VideoMode(HEIGHT, WIDTH, BIT_MODE), "Exodia");

  if (ac != 2)
    return 1;
  Map		*gameMap = new Map(av[1]);
  Player	player(gameMap);

  player.Initialize();
  player.LoadContent();
  while (window.IsOpened())
  {
    sf::Event	event;

    while (window.GetEvent(event))
    {
      if (event.Type == sf::Event::Closed || event.Key.Code == sf::Key::Escape)
	window.Close();
    }
    gameMap->Draw(window);
    player.Update(window);
    player.Draw(window);
    gameMap->DrawLife(window);
    window.Display();
  }
  return 0;
}
