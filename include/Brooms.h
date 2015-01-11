#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "Collision.h"
#include "ParticleSystem_b.h"


class Broom
{
 public:
 Broom(sf::Vector2f pos, sf::Vector2f vel) : 
  position(pos), velocity(vel), particle_emitter(50), collision(false), collision_with_player(false)
    {
      particle_emitter.setSpan(10);
    }

  void update(float delta_time, Player& player);

  void setPosition(sf::Vector2f position) { this->position = position; }
  const sf::Vector2f getPosition() const { return this->position; }

  void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
  const sf::Vector2f getVelocity() const { return this->velocity; }

  ParticleSystem_b::Emitter& getParticles() { return this->particle_emitter; }

  const bool isCollision_() const { return this->collision; }
  const bool isCollisionWithPlayer() const { return this->collision_with_player; }

 private:
  sf::Vector2f position;
  sf::Vector2f velocity;
  ParticleSystem_b::Emitter particle_emitter;
  bool collision;
  bool collision_with_player;
};

class BroomManager
{
 public:
 BroomManager(): brooms(), collision_with_player(false) {}

 void add(Broom& broom);
 Broom& get(std::size_t id);
 void deleteBroom(std::size_t id);

 const bool isCollisionWithPlayer() const { return this->collision_with_player; }

 const std::size_t size() const { return this->brooms.size(); }
 void clear() { brooms.clear(); collision_with_player = false; } 

 void update(float delta_time, Player& player);

 private:
 std::vector<Broom> brooms;
 bool collision_with_player;
};
