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

	//�趨�Ѷ�
	//��ȡˢ��ʱ�䡢�ߵ����
	int getSleepTime();
	int countList();
	int getScore();
private:
	struct Point
	{
		//������
		int x;
		int y;
		//ָ����
		Point *next;
	};
	Point *pHead;
	Wall &wall;
	Food &food;
	bool isrear;
};
extern HANDLE hOut ;//������ʾ���������
void gotoxy(HANDLE hOut, int x, int y);
