#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enviroment.hpp"
#include "Box.hpp"
#include <iostream>

enum
{
    stay,
    walk,
    jump,
    move
} STATE;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(640, 480), "Stack Attack");

    View view(FloatRect(0, 0, 640, 480));

    // Background
    Texture bg;
    bg.loadFromFile("assets/tmp_bg.png");
    Sprite background(bg);
    background.setOrigin(bg.getSize().x / 2, bg.getSize().y / 2);
    background.setPosition(view.getCenter());

    // Enviroment
    Enviroment env;

    // Player
    Player player(&env);

    // Box
    std::vector<Box *> boxes;

    Clock clock;
    Clock clock_box;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        if ((int)clock_box.getElapsedTime().asSeconds() == 1 && boxes.size() < 150)
        {
            Box *box = new Box(&env);
            boxes.push_back(box);
            clock_box.restart();
        }

        clock.restart();

        time = time / 500;

        if (time > 40)
            time = 40;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // UPDATE block
        player.update(time);
        for (Box *box : boxes)
            box->update(time);

        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 20; j++)
                env.box_matrix[i][j] = 0;
        for (Box *box : boxes)
        {
            int raw, col = 0;
            col = (box->position.first + 16) / 32;
            raw = (box->position.second + 16) / 32;
            env.box_matrix[raw][col] = 1;
            //std::cout << "BOX: RAW:" << raw << "\tCOL:" << col << std::endl;
        }

        std::cout << "PLAYER: " << (int)(player._x + 16) / 32 << " " << (int)(player._y + 48) / 32 << std::endl;

        for (Box *box : boxes)
            if (player.getRect().intersects(box->getRect()))
            {

                if (player._dy > 0)
                {
                    
                    player._y = box->getRect().top - 64;
                    //player._dy = 0;
                    player.setState();
                }
                if (player._dy < 0)
                {
                    player._y = box->getRect().top + 32;
                    player._dy = 0;
                    player.setState();
                }
                std::cout << "Collise" << std::endl;
            }

        for (Box *box : boxes)
            if (player.getRect().intersects(box->getRect()))
            {
                if (player._dx > 0)
                {
                    player._x = box->getRect().left - 32;
                }
                if (player._dx < 0)
                {
                    player._x = box->getRect().left + 32;
                }
                std::cout << "Collise" << std::endl;
            }

        window.setView(view);
        window.draw(background);
        for (Box *box : boxes)
        {
            box->draw(window);
        }
        player.draw(window);
        window.display();

        // for(Box* box: boxes)
        //     std::cout << box->num.first << " "<<  box->num.second << std::endl;
        // int count = 0;
        // for (int i = 0; i < 20; i++)
        // {
        //     count++;
        //     if (!env.box_matrix[14][i])
        //     {
        //         std::cout << " Count 20: " << count << std::endl;
        //         break;
        //     }
        // }

        // if (count == 1)
        // {
        //     Box* del_box = NULL;
        //     for (Box *box : boxes)
        //     {
        //         if(del_box!=NULL)
        //             boxes.erase(boxes);
        //         if (box->num.first == 14)
        //         {
        //             env.box_matrix[14][box->num.second] = 0;
        //             box->_hide = true;
        //         }
        //         box->max_y_col += 1;
        //         box->setState();

        //         int j,k=0;
        //         j = (int)box->position.second / 32 + 1;
        //         k = (int)box->position.first / 32 + 1;
        //         env.box_matrix[j][k] = env.box_matrix[j - 1][k];


        //     }
        // }
    }

    // while (window.isOpen())
    // {
    //     float time = clock.getElapsedTime().asMicroseconds();

    //     clock.restart();

    //     time = time / 500;

    //     if (time > 40)
    //         time = 40;

    //     Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == Event::Closed)
    //             window.close();
    //     }
    // }

    env.print_matrix();
    for (Box *box : boxes)
        delete box;
    return 0;
}