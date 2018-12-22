#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Textures.h"
#include <map>
#include <string>

using namespace sf;

class Player
{
    public:
        float _x,_y;
        float _dx, _dy; 
        
        Texture _texture;
        Sprite _sprite;

        enum {stay,walk,jump,move} STATE;

        std::map<std::string,bool> key;

        Player()
        {
            this->_texture.loadFromFile(PLAYER_TEXTURE_PATH);
            this->_sprite.setTexture(_texture);
            this->_x = 640/2;
            this-> _y = 416;
            this->_dx = 0;
            this->_dy = 0; 
            //this->_sprite.setOrigin(0,0);
            STATE = stay;
        };

        void draw(RenderWindow& window)
        {
            window.draw(_sprite);
        }

        void moving()
        {
            key["A"] = Keyboard::isKeyPressed(Keyboard::A);
            key["D"] = Keyboard::isKeyPressed(Keyboard::D);
            key["W"] = Keyboard::isKeyPressed(Keyboard::W);
            if(key["A"])
            {
                _dx = -0.1;
                if (STATE==stay) 
                    STATE=walk;
            }
            if(key["D"])
            {
                _dx = 0.1;
                if (STATE==stay) 
                    STATE=walk;
            }
            
            if(key["W"])
            {
                if (STATE==stay || STATE==walk) 
                { 
                    _dy=-0.27; 
                    STATE=jump; 
                }
            }

            
               
            if(!(key["A"] || key["D"]))
            {
                _dx=0;
			    if (STATE==walk) STATE=stay;
            }

            if (!Keyboard::isKeyPressed(Keyboard::W))
		    {
			    
		    }


            // if(Keyboard::isKeyPressed(Keyboard::S))
            //     _y += 1;
            key["A"]=key["D"]=key["W"]=false;

            _sprite.setPosition(this->_x,this->_y);
        };

        void update(float time)
        {
            moving();

            if(STATE == jump) _dy += 0.0005*time; 

            

            _x += _dx*time;
            _y += _dy*time;
            if (_y >416)
            {
                _y = 416;
                STATE = stay;
                _dy = 0;
            }
            if (_x > 608)
                _x = 608;       
            if (_x < 0)
                _x = 0;
        };

};

#endif