#pragma once

#include <SFML/Graphics.hpp>

#define BAT_SPEED 6

class Player
{
 public:
  Player() { pos = sf::Vector2f(100,100);}
  void update();
  const sf::Vector2f getPosition() {return pos;}
 private:
  sf::Vector2f pos;
};
