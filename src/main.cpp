#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "../include/ResourceMenager.h"
#include "../include/player.h"
#include "../include/ParticleSystem_b.h"
// sprawdzanie kolizji AABB 
bool isCollision(float x1, float y1, float w1, float h1,
                 float x2, float y2, float w2, float h2 )
{
    if( x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2 )
        return( true );
    return( false );
}

// enemies informations
struct Broom
{
  Broom(sf::Vector2f p, sf::Vector2f v) : pos(p), vel(v), particle_emitter(50)
  {
    particle_emitter.setSpan(10);
  }
  sf::Vector2f pos;
  sf::Vector2f vel;
  ParticleSystem_b::Emitter particle_emitter;
};

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

  std::vector<Broom> brooms;

  sf::Clock respawn_brooms_clock;
  respawn_brooms_clock.restart();
  sf::Clock score_clock;
  score_clock.restart();
  float last_time = 0;


  // state: 0-menu, 1-game
  int state = 0;
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
      if(state == 1)
	{
	  if(respawn_brooms_clock.getElapsedTime() > sf::milliseconds(500))
	    {
	      brooms.push_back(Broom(sf::Vector2f(800, rand()%500+1), sf::Vector2f(-(rand()%10+4), 0)));
	      respawn_brooms_clock.restart();
	    }

	  for(size_t i = 0; i < brooms.size(); i++)
	    {
	      
	      if(isCollision(brooms[i].pos.x, brooms[i].pos.y+10, 130, 75,
			     player.getPosition().x, player.getPosition().y, 36, 36))
		{
		  last_time = score_clock.getElapsedTime().asSeconds();
		  score_clock.restart();
		  brooms.clear();
		  state = 0;
		  break;
		}
	      
	      brooms[i].pos += brooms[i].vel;
	      
	      brooms[i].particle_emitter.setPosition(brooms[i].pos.x+160,
						     brooms[i].pos.y+70);
	      brooms[i].particle_emitter.update();
	      if(brooms[i].pos.y < 0)
		brooms.erase(brooms.begin() + i);
	    }

	  player.update();
	  spr_bat.setPosition(player.getPosition());

	  std::ostringstream string_score;
	  string_score << score_clock.getElapsedTime().asSeconds();
  
	  text_score.setString(string_score.str());
	  sf::FloatRect textRect = text_score.getLocalBounds();
	  text_score.setOrigin(textRect.left + textRect.width/2.0f,
			       textRect.top  + textRect.height/2.0f);
	  text_score.setPosition(sf::Vector2f(400,textRect.top  + textRect.height/2.0f));

	  window.clear(sf::Color(32,32,32));
	  window.draw(text_score);
	  window.draw(spr_bat);
	  for(size_t i = 0; i < brooms.size(); i++)
	    {
	      for(size_t x = 0; x < brooms[i].particle_emitter.getNumberOfParticles(); x++)
                {
		  spr_particle.setPosition(brooms[i].particle_emitter.getParticle(x).position.x,
					   brooms[i].particle_emitter.getParticle(x).position.y);
		  window.draw(spr_particle);
		}
	      spr_broom.setPosition(brooms[i].pos);
	      window.draw(spr_broom);
	    }
	  window.display();
	}
      else if(state == 0)
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
	      state = 1;
	    }

	  window.clear();
	  window.draw(text_menu);
	  window.display();
	}
    }
  return EXIT_SUCCESS;
}
