#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include "pipe.h"
using namespace sf;

const int N = 6;
int ts = 54; //tile size
Vector2f offset(65, 55);
int sizeOn = 0;
int size = 0;

pipe grid[N][N];
pipe &cell(Vector2i v) { return grid[v.x][v.y]; }
bool isOut(Vector2i v) { return !IntRect(0, 0, N, N).contains(v); }

void generatePuzzle()
{
  std::vector<Vector2i> nodes;
  nodes.push_back(Vector2i(rand() % N, rand() % N));

  while (!nodes.empty())
  {
    int n = rand() % nodes.size();
    Vector2i v = nodes[n];
    Vector2i d = DIR[rand() % 4]; // Random side of pipe

    if (cell(v).dirs.size() == 3)
    {
      nodes.erase(nodes.begin() + n);
      continue;
    }
    if (cell(v).dirs.size() == 2)
      if (rand() % 50)
        continue;

    bool complete = 1;
    for (auto D : DIR)
      if (!isOut(v + D) && cell(v + D).dirs.empty())
        complete = 0;
    if (complete)
    {
      nodes.erase(nodes.begin() + n);
      continue;
    }

    if (isOut(v + d))
      continue;
    if (!cell(v + d).dirs.empty())
      continue;
    cell(v).dirs.push_back(d);
    cell(v + d).dirs.push_back(-d);
    nodes.push_back(v + d);
  }
}

void drop(Vector2i v)
{
  if (cell(v).on)
    return;

  cell(v).on = true;

  for (auto d : DIR)
    if (!isOut(v + d))
      if (cell(v).isConnect(d) && cell(v + d).isConnect(-d))
        drop(v + d);
}

enum GameMode
{
  START,
  GAME,
  WIN
};

int main()
{
  srand(time(0));
  GameMode state = START;
  RenderWindow app(VideoMode(390, 390), "The Pipe Puzzle!");

  Texture t1, t2, t3, t4;
  t1.loadFromFile("images/bg_menu.png");
  t2.loadFromFile("images/comp.png");
  t3.loadFromFile("images/server.png");
  t4.loadFromFile("images/pipes.png");
  t4.setSmooth(true);

  Sprite sBackground(t1), sComp(t2), sServer(t3), sPipe(t4);
  sPipe.setOrigin(27, 27);
  sComp.setOrigin(18, 18);
  sServer.setOrigin(20, 20);

  generatePuzzle();

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
    {
      pipe &p = grid[j][i];

      for (int n = 4; n > 0; n--) //find orientation//
      {
        std::string s = "";
        for (auto d : DIR)
          s += p.isConnect(d) ? '1' : '0';
        if (s == "0011" || s == "0111" || s == "0101" || s == "0010")
          p.orientation = n;
        p.rotate();
      }

      for (int n = 0; n < rand() % 4; n++) //shuffle//
      {
        grid[j][i].orientation++;
        grid[j][i].rotate();
      }
    }

  Vector2i servPos;
  while (cell(servPos).dirs.size() == 1)
  {
    servPos = Vector2i(rand() % N, rand() % N);
  }
  sServer.setPosition(Vector2f(servPos * ts));
  sServer.move(offset);

  Music music;
  music.openFromFile("music.wav");
  music.play();
  music.setLoop(true);

  while (app.isOpen())
  {
    if (state == WIN)
    {
      t1.loadFromFile("images/bg_win.png");
      Sprite sBackground(t1);
    }
    Event e;
    while (app.pollEvent(e))
    {
      if (e.type == Event::Closed)
        app.close();

      if (e.type == Event::MouseButtonPressed)
        if (e.key.code == Mouse::Left)
        {
          if (state == START)
          {
            state = GAME;
            t1.loadFromFile("images/background.png");
            Sprite sBackground(t1);
            continue;
          }
          if (state == WIN)
            app.close();

          Vector2i pos = Mouse::getPosition(app) + Vector2i(ts / 2, ts / 2) - Vector2i(offset);
          pos /= ts;
          if (isOut(pos))
            continue;
          cell(pos).orientation++;
          cell(pos).rotate();

          for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
              grid[j][i].on = 0;

          drop(servPos);
        }
    }

    app.clear();
    app.draw(sBackground);
    if (state == GAME)
    {
      for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
          pipe &p = grid[j][i];

          int kind = p.dirs.size();
          if (kind == 2 && p.dirs[0] == -p.dirs[1])
            kind = 0;

          p.angle += 5;
          if (p.angle > p.orientation * 90)
            p.angle = p.orientation * 90;

          sPipe.setTextureRect(IntRect(ts * kind, 0, ts, ts));
          sPipe.setRotation(p.angle);
          sPipe.setPosition(j * ts, i * ts);
          sPipe.move(offset);
          app.draw(sPipe);

          if (kind == 1)
          {
            if (p.on)
              sComp.setTextureRect(IntRect(53, 0, 36, 36));
            else
            {
              size++;
              sComp.setTextureRect(IntRect(0, 0, 36, 36));
            }
            sComp.setPosition(j * ts, i * ts);
            sComp.move(offset);
            app.draw(sComp);
          }
        }
      if (size == 0)
        state = WIN;
      std::cout << size << std::endl;
      size = 0;

      app.draw(sServer);
    }

    if (state == START)
      app.draw(sBackground);
    app.display();
  }

  return 0;
}
