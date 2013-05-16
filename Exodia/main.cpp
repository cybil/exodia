
#include <iostream>

#include "MainWin.hpp"

using namespace sf;


int		main()
{
  // RenderWindow	app(VideoMode(800, 600, 32), "BLAAAA");
  MainWin	win;
  Image		image;

  win.initSprite();
  win.loadMap("map1.map");
  win.mainLoop();
  return (0);
}
