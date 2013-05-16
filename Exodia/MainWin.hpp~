

#include <vector>
#include <SFML/Graphics.hpp>

class MainWin
{
public:
  MainWin();
  ~MainWin();

  void		initSprite();
  void		display();
  void		mainLoop();
  void		loadMap(const std::string &);
  void		displayMap();
  void		moveSprite();
  void		checkFall();
private:
  sf::Sprite			_actSp;
  sf::Image			_img;
  std::vector<sf::Sprite *>	_spList;
  sf::RenderWindow		_app;
  std::map<int, std::string>	_map;
  sf::Sprite			_border;
  sf::Image			_borderImg;
};
