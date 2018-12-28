#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enviroment.hpp"
#include "Box.hpp"
#include <iostream>

enum {stay,walk,jump,move} STATE;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(640, 480), "Stack Attack");

	View view( FloatRect(0, 0, 640, 480) );

    // Background
    Texture bg;
	bg.loadFromFile("assets/tmp_bg.png");
    Sprite background(bg);
    background.setOrigin(bg.getSize().x/2,bg.getSize().y/2);
    background.setPosition(view.getCenter());

    // Enviroment
    Enviroment env;

    // Player
    Player player(&env);

  

    // Box
    std::vector<Box*> boxes;

    Clock clock;
    Clock clock_box;

    while(window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        if((int)clock_box.getElapsedTime().asSeconds() == 1 && boxes.size() < 30)
        {
            Box* box = new Box(&env); 
            boxes.push_back(box);
            clock_box.restart();
        }
            
            
		clock.restart();

		time = time/500;  

		if (time > 40) time = 40;

        Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

        // UPDATE block
        player.update(time);
        for (Box* box : boxes) 
            box->update(time);

        for (Box* box : boxes)
            if(player.getRect().intersects(box->getRect())){
                if (player._dy>0){ player._y = box->getRect().top -  64;  player._dy=0; player.setState();}
				if (player._dy<0){ player._y = box->getRect().top + 32 ;   player._dy=0;}
                if (player._dx>0)	{ player._x =  box->getRect().left -  32; }
				if (player._dx<0)	{ player._x =  box->getRect().left + box->getRect().width ;}
            }

        window.setView(view);
        window.draw(background);
        for (Box* box : boxes)
        { 
            box->draw(window);
        }
        player.draw(window);
        window.display();
    }

    for(Box* box: boxes)
        delete box;
    return 0;
}