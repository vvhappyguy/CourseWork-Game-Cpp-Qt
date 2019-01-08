#include <SFML/Graphics.hpp>

using namespace sf;

Vector2i Up(0, -1);
Vector2i Down(0, 1);
Vector2i Right(1, 0);
Vector2i Left(-1, 0);

Vector2i DIR[4] = {Up, Right, Down, Left};

struct pipe
{
  std::vector<Vector2i> dirs;
  int orientation;
  float angle;
  bool on;

  pipe() { angle = 0; }

  void rotate()
  {
    for (int i = 0; i < dirs.size(); i++)
      if (dirs[i] == Up)
        dirs[i] = Right;
      else if (dirs[i] == Right)
        dirs[i] = Down;
      else if (dirs[i] == Down)
        dirs[i] = Left;
      else if (dirs[i] == Left)
        dirs[i] = Up;
  }

  bool isConnect(Vector2i dir)
  {
    for (auto d : dirs)
      if (d == dir)
        return true;
    return false;
  }
};