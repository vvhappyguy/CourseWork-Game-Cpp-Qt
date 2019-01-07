#ifndef BOX_H
#define BOX_H

#include <SFML/Graphics.hpp>
#include "Textures.h"
#include "Enviroment.hpp"
#include <cstdlib>
#include <iostream>
#include <utility>

using namespace sf;


class Box
{
    public:
        // Positions
        std::pair<float, float> position; // x,y
        std::pair<float, float> cnt_pos; // center x,y
        std::pair<SUInt, SUInt> num; // raw, col
        SUInt max_raw = 0; // max y level

        // Texture
        Texture _texture;
        Sprite _sprite;

        // Game Env pointer
        Enviroment* env;

        // Speed
        const float _dy = 0.1; // Always down
        float _dx = 0; // Only if collision with Player

        bool _hide = false;

        // State ???
        enum {fall,stay} STATE;
        SUInt max_y_col;

        Box(Enviroment* env)
        {
            // Save pointer to env
            this->env = env;

            // Texture
            this->_texture.loadFromFile(BOX_TEXTURE_PATH);
            this->_sprite.setTexture(_texture);

            // Generate random col
            this->num.second = (rand()%20);
            // this->num.second = 0;
            this->max_y_col = env->countYbyColumn(num.second);
            this->num.first = this->max_y_col;
            
            this->position.first = this->num.second*32;
            this->position.second = 0;

            STATE = fall;

            
            //env->box_matrix[num.first][num.second] = true;
            //std::cout << "Box c-tor "<< num.second << " max_y_col:" << max_y_col <<  std::endl;
        };

        FloatRect getRect()
	    {
		    return FloatRect(this->position.first,this->position.second,32,32);
	    }

        void draw(RenderWindow& window)
        {
            if(this->_hide)
                return;
            //std::cout << "Draw box" << std::endl;
            //std::cout << (_sprite.getPosition().y) << " " << this->_y << std::endl;
            window.draw(this->_sprite);
        };

        void setState()
        {
            this->STATE = fall;
        }
        void update(float time)
        {
            if (STATE == stay)
                return;
            num = env->getPosition(position.first,position.second);
            position.second += _dy*time;
                if (position.second > this->max_y_col*32)
                {
                    position.second = this->max_y_col*32;
                    STATE = stay;
                    // env->box_matrix[num.first][num.second] = 1;
                }
            // std::cout << "Position: " << position.first << " " << position.second << std::endl;
            _sprite.setPosition(position.first,position.second);
        };
};

#endif