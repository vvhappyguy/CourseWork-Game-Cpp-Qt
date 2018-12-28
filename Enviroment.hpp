#ifndef ENV_H
#define ENV_H

#include <utility>

class Enviroment
{
    public:
        bool box_matrix[15][20];
        Enviroment()
        {
            for(int i = 0; i < 15; i++)
                for(int j = 0; j < 20; j++)
                    box_matrix[i][j] = 0;
        };

        short int getMaxYbyColumn(size_t col)
        {
            return countYbyColumn(col) * 32;
        };

        short int countYbyColumn(size_t col)
        {
            short int count =0;
            for (int i = 14; i >= 0; i--)
                if(box_matrix[col])
                    count++;
                else
                    return count;
            return count;
        };

        std::pair<short int, short int> getPostion(float x, float y)
        {
            return std::pair<short int, short int>((short int)x/20, (short int)x/15);
        };


};

#endif