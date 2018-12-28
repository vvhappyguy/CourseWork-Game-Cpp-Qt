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
        std::pair<float, float> position;
        std::pair<short, short> num;
        float max_y_col = 0;
        short int col  = -1;
        const float _dy = 0.1;
        float _dx = 0;
        int y_col;
        Enviroment* env;
        Texture _texture;
        Sprite _sprite;
        enum {fall,stay} STATE;

    Box(Enviroment* env)
        {
            this->col = (rand()%20);
            this->max_y_col = env->getMaxYbyColumn(col) - 32;
            this->y_col = env->countYbyColumn(col);

            std::cout << "Box c-tor "<< max_y_col <<" " << y_col << std::endl;
            this->_texture.loadFromFile(BOX_TEXTURE_PATH);
            this->_sprite.setTexture(_texture);
            position.first = col*32;
            position.second = 0;
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
            num = env->getPostion(position.first,position.second);
            position.second += _dy*time;
                if (position.second > max_y_col)
                {
                    position.second = max_y_col;
                    STATE = stay;
                    env->box_matrix[col][y_col] = 1;
                }
            _sprite.setPosition(position.first,position.second);
        };
};

#endif