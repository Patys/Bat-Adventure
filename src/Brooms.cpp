#include "../include/Brooms.h"
#include <iostream>

void Broom::update(float delta_time, Player& player)
{
  sf::Vector2f next_position = this->getPosition() + this->getVelocity() * delta_time;
  this->setPosition(next_position);

  this->particle_emitter.setPosition(this->getPosition().x+160,
				     this->getPosition().y+70);
  this->particle_emitter.update();

  bool collision_with_player = isCollision(this->getPosition(), sf::Vector2f(167,94),
					    player.getPosition(), sf::Vector2f(36,36));
  bool collision_with_left = isCollision(this->getPosition(), sf::Vector2f(167,96),
					  sf::Vector2f(-167,0), sf::Vector2f(1,600));

  if(collision_with_player || collision_with_left)
    {
      this->collision = true;
    }
  if(collision_with_player)
    {
      this->collision_with_player = true;
    }
}

void BroomManager::add(Broom& broom)
{
  this->brooms.push_back(broom);
}

Broom& BroomManager::get(std::size_t id)
{
  return this->brooms.at(id);
}

void BroomManager::deleteBroom(std::size_t id) 
{
  this->brooms.erase(this->brooms.begin() + id);
}


void BroomManager::update(float delta_time, Player& player)
{
  for(std::size_t i = 0; i < this->size(); i++)
    {
      this->brooms[i].update(delta_time, player);
      
      if(brooms[i].isCollisionWithPlayer())
	{
	  this->collision_with_player = true;
	}

      if(brooms[i].isCollision_())
	{
	  this->deleteBroom(i);
	}
    }
}
