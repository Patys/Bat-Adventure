#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "../include/ResourceMenager.h"
#include "../include/ParticleSystem_b.h"
#include "../include/Player.h"
#include "../include/Brooms.h"

enum GAME_STATE {GAME, MENU};

int main()
{
  srand(time(0));

  sf::RenderWindow window(sf::VideoMode(800, 600), "Bat Adventure", sf::Style::Close);
  window.setFramerateLimit(60);

  ResourceMenager tex_manager;
  
  sf::Sprite spr_bat(tex_manager.getTexture("data/bat.png"));
  sf::Sprite spr_broom(tex_manager.getTexture("data/witch.png"));
  sf::Sprite spr_particle(tex_manager.getTexture("data/star5.png"));

  sf::Font font;
  font.loadFromFile("data/Raleway-Regular.otf");

  sf::Text text_score("", font, 36);
  sf::Text text_menu("Type e to start.\n\nLast time: 0 \n\nGame created by Patys :D", font, 36);

  Player player;

  BroomManager brooms;

  sf::Clock respawn_brooms_clock;
  sf::Clock score_clock;
  sf::Clock game_clock;

  int last_time = 0;

  GAME_STATE state = MENU;

  while (window.isOpen())
    {
      // Process events
      sf::Event event;
      while (window.pollEvent(event))
	{
	  // Close window : exit
	  if (event.type == sf::Event::Closed)
	    window.close();
	  
	}
      if(state == GAME)
	{
	  if(respawn_brooms_clock.getElapsedTime() > sf::milliseconds(500))
	    {
	      Broom broom(sf::Vector2f(800, rand()%500+1), sf::Vector2f(-(rand()%500+200), 0));
	      brooms.add(broom);
	      respawn_brooms_clock.restart();
	    }

	  if(brooms.isCollisionWithPlayer())
	    {
	      brooms.clear();
	      last_time = (int)score_clock.getElapsedTime().asSeconds();
	      score_clock.restart();
	      state = MENU;
	    }

	  player.update();
	  brooms.update(game_clock.restart().asSeconds(), player);

	  std::ostringstream string_score;
	  string_score << (int)score_clock.getElapsedTime().asSeconds();
  
	  text_score.setString(string_score.str());
	  sf::FloatRect textRect = text_score.getLocalBounds();
	  text_score.setOrigin(textRect.left + textRect.width/2.0f,
			       textRect.top  + textRect.height/2.0f);
	  text_score.setPosition(sf::Vector2f(400,textRect.top  + textRect.height/2.0f));

	  window.clear(sf::Color(32,32,32));
	  window.draw(text_score);
	  spr_bat.setPosition(player.getPosition());
	  window.draw(spr_bat);
	  for(size_t i = 0; i < brooms.size(); i++)
	    {
	      for(size_t x = 0; x < (size_t)brooms.get(i).getParticles().getNumberOfParticles(); x++)
                {
		  spr_particle.setPosition(brooms.get(i).getParticles().getParticle(x).position.x,
					   brooms.get(i).getParticles().getParticle(x).position.y);
		  window.draw(spr_particle);
		}
	      spr_broom.setPosition(brooms.get(i).getPosition());
	      window.draw(spr_broom);
	    }
	  window.display();
	}
      else if(state == MENU)
	{
	  std::ostringstream string_score;
	  string_score << last_time;
  
	  text_menu.setString("Crazy witches rushing to magic cave.\nRun away!!!\n\nType e to START.\nControls: WSAD.\n\nLast time: " + string_score.str() + "\n\nGame created by Patys.");
	  sf::FloatRect textRect = text_score.getLocalBounds();
	  text_menu.setOrigin(textRect.left + textRect.width/2.0f,
			       textRect.top  + textRect.height/2.0f);
	  text_menu.setPosition(sf::Vector2f(textRect.left + textRect.width/2.0f+50 ,textRect.top + textRect.height/2.0f + 10));

	  if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	    {
	      brooms.clear();
	      state = GAME;
	      score_clock.restart();
	    }

	  window.clear();
	  window.draw(text_menu);
	  window.display();
	}
    }
  return EXIT_SUCCESS;
}
