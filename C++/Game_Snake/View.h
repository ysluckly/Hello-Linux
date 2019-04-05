#pragma once 

#include "Model.h"
#include <stdio.h>
#include <windows.h>

void SetPos(int X, int Y)
{
  HANDLE hStdout = GETStdHandle(STD_OUTPUT_HANDLE);
  COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(hStdout, coord);
}

//显示外墙
void DisplayWall(int width, int height)
{
  //上边的墙
  SetPos(0, 0);
  int i = 0;
  for( ; i < width + 2; i++)
  {
    printf("#");
  }

  //下面的墙
  SetPos(0, height + 1);
  for( ; i < width + 2; i++)
  {
    printf("#");
  }
  
  //左边的墙
  for( ; i< height + 2; i++)
  {
    SetPos(0, i);
    printf("#");
  }

  //右边的墙
  for( ; i< height + 2; i++)
  {
    SetPos(width + 1, i);
    printf("#");
  }
}

void CleanSnakeNode(Position pos)
{
  //这里采用的下标所以需要加1
  SetPos(pos.x + 1, pos.y + 1);
  printf(" ");
}

void DisplaySnakeNode(Position pos)
{
  //这里采用的下标所以需要加1
  SetPos(pos.x + 1, pos.y + 1);
  printf("@");
}

void DisplayFoodNode(Position pos)
{
  //这里采用的下标所以需要加1
  SetPos(pos.x + 1, pos.y + 1);
  printf("$");
}

void DisplaySnake(const Snake* pSnake)
{
  Node* pNode = pSnake->pHead;
  while (pNode)
  {
    DisplaySnakeNode(pNode->position);
    pNode = pNode->pNext;
  }
}
