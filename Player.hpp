#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Textures.h"

using namespace sf;

class Player
{
    public:
        short int _x,_y;
        Texture _texture;
        Sprite _sprite;

        enum {stay,walk,jump,move} STATE;

        Player()
        {
            this->_texture.loadFromFile(PLAYER_TEXTURE_PATH);
            this->_sprite.setTexture(_texture);
            this->_x = 640/2;
            this-> _y = 480;
            this->_sprite.setOrigin(_x,_y);
            STATE = stay;
        };

        void draw(RenderWindow& window)
        {
            window.draw(_sprite);
        }

        void moving()
        {
            if(Keyboard::isKeyPressed(Keyboard::A))
                _x -= 1;
            if(Keyboard::isKeyPressed(Keyboard::D))
                _x += 1;
            if(Keyboard::isKeyPressed(Keyboard::W))
                _y -= 1;
            if(Keyboard::isKeyPressed(Keyboard::S))
                _y += 1;
            _sprite.setPosition(this->_x,this->_y);
        };

        void update()
        {
            moving();
        };

};

#endif