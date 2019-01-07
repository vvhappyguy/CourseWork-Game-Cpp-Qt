#ifndef ENV_H
#define ENV_H

#include <utility>
#include <vector>
#include <iostream>

class Enviroment
{
  public:
    bool box_matrix[15][20]; // y,x
    Enviroment()
    {
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 20; j++)
                box_matrix[i][j] = 0;
    };

    short int getMaxYbyColumn(size_t col)
    {
        return countYbyColumn(col) * 32;
    };

    short int countYbyColumn(size_t col)
    {
        short int j = -1;
        for (int i = 0; i < 15; i++)
            if (this->box_matrix[i][col] == 0)
                j += 1;
        return j;
    };

    std::pair<short int, short int> getPosition(float x, float y)
    {
        return std::pair<short int, short int>((short int)(y + 16) / 32, (short int)(x+16) / 32);
    };

    void print_matrix()
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 20; j++)
                std::cout << this->box_matrix[i][j];
            std::cout << std::endl;
        }
    }
};

#endif