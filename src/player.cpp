#include "../include/player.h"

void Player::update()
{
  sf::Vector2f vel(0,0);
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
      vel.y = -BAT_SPEED;
    }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
      vel.y = BAT_SPEED;
    }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
      vel.x = -BAT_SPEED;
    }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
      vel.x = BAT_SPEED;
    }
  // collision with borders
  //                                  size sprite
  if(pos.x + vel.x < 0 || pos.x + vel.x + 36 > 800)
    vel.x = 0;
  if(pos.y + vel.y < 0 || pos.y + vel.y + 36 > 600)
    vel.y = 0;

  pos += vel;
}
