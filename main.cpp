#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include <iostream>


using namespace sf;

int main()
{
    RenderWindow window(VideoMode(640, 480), "Stack Attack");

	View view( FloatRect(0, 0, 450, 280) );

    // Background
    Texture bg;
	bg.loadFromFile("assets/tmp_bg.png");
    Sprite background(bg);
    background.setOrigin(bg.getSize().x/2,bg.getSize().y/2);
    background.setPosition(view.getCenter());


    // Player
    Player player;

    // Box
    Texture box_texture;
    box_texture.loadFromFile("assets/wall.png");
    Sprite box_sprite(box_texture);
    box_sprite.setPosition(0,0);
    float box_x = 0;
    float box_y = 0 ;

    Clock clock;

    while(window.isOpen())
    {

        Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

        player.update();

        box_y += 0.1;
        box_sprite.setPosition(box_x,box_y);

        window.setView(view);
        window.draw(background);
        player.draw(window);
        window.draw(box_sprite);
        window.display();
    }
    return 0;
}