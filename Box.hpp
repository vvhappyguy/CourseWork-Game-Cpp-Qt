#ifndef BOX_H
#define BOX_H

#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Enviroment.hpp"
#include <cstdlib>
#include <iostream>

using namespace sf;

class Box
{
    public:
        float _x,_y;
        const float _dy = 0.1;
        float _dx = 0;
        Enviroment* env;
        Texture _texture;
        Sprite _sprite;
        enum {fall,stay} STATE;

    Box(Enviroment*)
        {
            std::cout << "Box c-tor" << std::endl;
            this->_texture.loadFromFile(BOX_TEXTURE_PATH);
            this->_sprite.setTexture(_texture);
            this->_x = (rand()%20)*32;
            this-> _y = 0;
            this->_dx = 0;
            this->env = env;
            STATE = fall;
        };

        void draw(RenderWindow& window)
        {
            //std::cout << "Draw box" << std::endl;
            //std::cout << (_sprite.getPosition().y) << " " << this->_y << std::endl;
            window.draw(this->_sprite);
        };


        void update(float time)
        {
            this->_y += _dy*time;
               

                std::cout << _y << std::endl;
                if (this->_y > 448)
                {
                    this->_y = 448;
                    STATE = stay;
                }
                

            
            _sprite.setPosition(this->_x,this->_y);
            //std::cout << this->_y << std::endl;
        };
};

#endif