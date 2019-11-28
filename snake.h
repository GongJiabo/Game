#pragma once
#include<iostream>
#include"wall.h"
#include"food.h"
#include<Windows.h>
using namespace std;

class Snake
{
public:
	Snake(Wall &tempwall,Food &tempfood);

	enum{ UP = 'w',DOWN = 's',LEFT = 'a', RIGHT = 'd' };

	void initSnake();
	void destroyPoint();
	void addPoint(int x, int y);
	void deletePoint();
	bool move(char key);

	//设定难度
	//获取刷屏时间、蛇的身段
	int getSleepTime();
	int countList();
	int getScore();
private:
	struct Point
	{
		//数据域
		int x;
		int y;
		//指针域
		Point *next;
	};
	Point *pHead;
	Wall &wall;
	Food &food;
	bool isrear;
};
extern HANDLE hOut ;//定义显示器句柄变量
void gotoxy(HANDLE hOut, int x, int y);
