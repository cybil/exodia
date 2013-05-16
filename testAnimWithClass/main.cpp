#include <SFML/Graphics.hpp>

const int	sDown = 0;
const int	sRight = 0;
const int	sLeft = 0;
const int	sUp = 0;

int		main()
{
  sf::RenderWindow	window(sf::VideoMode(800, 600, 32), "Exodia");

  while (window.IsOpended())
  {
    sf::Event	event;

    while (window.GetEvent(event))
    {
      if (event.Type == sf::Event::Closed || event.Key.Code == sf::Key::Escape)
	window.Close();
    }
  }
  return 0;
}
