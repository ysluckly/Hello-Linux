#pragma once 

#include "View.h"
#include <assert.h>
#include <stdlib.h>
#include "Model.h"
#include <stdio.h>
#include <unistd.h>

void SnakeInit(Snake* pSnake)
{
  //对于最后一个节点的下一个位置必须置为空
  pSnake->pHead = NULL;
  int i = 0;
  for (; i < 3; i++)
  {
    Position pos;
    pos.x = i + 5;
    pos.y = 5;

    Node* pNewNode = (Node*)malloc(sizeof(Node));
    assert(pNewNode);

    pNewNode->position = pos;
    pNewNode->pNext = pSnake->pHead;
    pSnake->pHead = pNewNode;
  }

  pSnake->direction = RIGHT;
}

//1.重叠
//2.不重叠
int IsOverlapSnake(int x, int y, const Snake* pSnake)
{
  Node* pNode;
  for (pNode = pSnake->pHead; pNode; pNode = pNode->pNext)
  {
    if (pNode->position.x == x && pNode->position.y == y)
    {
      return 1;
    }
  }

  return 0;
}

//生成食物
//1.随机
//2.范围内
//3.不和蛇重叠
void FoodInit(Position* pFood, int width, int height, const Snake* pSnake)
{
  int x, y;
  do
  {
    x = rand() % width;
    y = rand() % height;
  }while (IsOverlapSnake(x, y, pSnake));

  pFood->x = x;
  pFood->y = y;
}

void GameInit(Game* pGame)
{


  //采用头插
  SnakeInit(&(pGame->snake));

  pGame->score = 0;
  pGame->scorePerFoof = 10;
  pGame->speed = 200;//毫秒
  pGame->width = 28;
  pGame->height = 27;
  //对于食物的初始化一定要放在后面，因为需要知道高和宽
  FoodInit(&(pGame->foodPosition), pGame->width, pGame->height, &(pGame->snake));
}
//下一步的坐标
Position GetNextPoision(const Snake* pSnake)
{
  Position nextPos;
  nextPos.x = pSnake->pHead->position.x;
  nextPos.y = pSnake->pHead->position.y;
  switch (pSnake->direction)
  {
    case UP:
      nextPos.y -= 1;
      break;
    case DOWN:
      nextPos.y += 1;
      break;
    case LEFT:
      nextPos.x -= 1;
      break;
    case RIGHT:
      nextPos.x += 1;
      break;
  }

  return nextPos;
}

void PushFront(Snake* pSnake, Position nextPos)
{
  Node* pNewNode = (Node*)malloc(sizeof(Node));
  assert(pNewNode);

  pNewNode->position = nextPos;
  pNewNode->pNext = pSnake->pHead;
  pSnake->pHead = pNewNode;

  //显示增加的结点
  DisplaySnakeNode(nextPos);
}

void PopBack(Snake* pSnake)
{
  Node* pNode = pSnake->pHead;

  //head->()->()->()
  while (pNode->pNext->pNext != NULL)
  {
    pNode = pNode->pNext;
  }
  //删除结点的，不再显示，删除的结点
  CleanSnakeNode(pNode->pNext->position);
  free(pNode->pNext);
  pNode->pNext = NULL;
}

int IsCrashByWall(int width, int height, Position nextPos)
{
  if (nextPos.x < 0 || nextPos.x >= width)
  {
    return 1;
  }
  if (nextPos.y < 0 || nextPos.y >= height)
  {
    return 1;
  }

  return 0;
}

//1.表示没撞
//0.表示撞了
int IsCrashHimself(Snake* pSnake)
{
  //使用蛇头和所有结点进行比较
  Node* pHead = pSnake->pHead;//第一个结点
  Node* pNode = pSnake->pHead->pNext;//第二个结点
  
  while (pNode != NULL)
  {
    if (pHead->position.x == pNode->position.x && pHead->position.y == pNode->position.y)
    {
      return 1;
    }
    pNode = pNode->pNext;
  }

  return 0;
}

void GameStart()
{
  Game game;
  GameInit(&game);

  DisplayWall(game.width, game.height);
  DisplaySnake(&(game.snake));
  DisplayFoodNode(game.foodPosition);
  while (1)
  {
    if (GetAsyncKeyState(VK_UP) && game.snake.direction != DOWN)
    {
      game.snake.direction = UP;
    }
    if (GetAsyKeyncState(VK_DOWN) && game.snake.direction != UP)
    {
      game.snake.direction = DOWN;
    }
    if (GetAsyncKeyState(VK_LEFT) && game.snake.direction != RIGHT)
    {
      game.snake.direction = LEFT;
    }
    if (GetAsyKeyncState(VK_RIGHT) && game.snake.direction != LEFT)
    {
      game.snake.direction = RIGHT;
    }
    Position nextPos = GetNextPoision(&(game.snake));
    if (nextPos.x == game.foodPosition.x && nextPos.y == game.foodPosition.y)
    {
      //吃到食物,蛇增加一格
      PushFront(&(game.snake), nextPos);
      game.score += game.scorePerFoof;

      //生成新食物
      FoodInit(&(game.foodPosition), game.width, game.height, &(game.snake));
      DisplayFoodNode(game.foodPosition);
    }
    else 
    {
      //没吃到食物
      PushFront(&(game.snake), nextPos);
      PopBack(&(game.snake));
    }

    if (IsCrashByWall(game.width, game.height, nextPos))
    {
      //扩展撞墙，失败了放个歌曲，打印搞笑的字
      break;
    }

    if (IsCrashHimself(&(game.snake)))
    {
      break;
    }
    usleep(game.speed);
  }
}
