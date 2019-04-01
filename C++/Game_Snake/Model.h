#pragma once 

//坐标原点位于坐上角
//向右为x轴正方向
//向下为y轴正方向
typedef struct 
{
  int x;
  int y;
}Position;

//链表结点
typedef struct Node
{
  Position position;
  struct Node* pNext;
}Node;

//蛇的当前的前进方向
typedef enum Direction
{
  UP, DOWN, LEFT, RIGHT
}Direction;

//蛇的结构
typedef struct Snake
{
  Direction direction;
  Node* pHead;//保存链表的头结点
}Snake;

//一盘游戏中用到的非独立字段
typedef struct Game
{
  Snake snake;
  Position foodPosition;
  int score;//当前得分
  int scorePerFoof;//没吃一个食物得分
  int speed;//蛇的前进速度
  int width;//宽
  int height;//高
}Game;
