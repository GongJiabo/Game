#include "snake.h"
#include<Windows.h>

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;             //横坐标
	pos.Y = y;            //纵坐标
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

Snake::
Snake(Wall &tempwall,Food &tempfood):wall(tempwall),food(tempfood)
{
	pHead = NULL;
	isrear = false;
}

void Snake::initSnake()
{
	destroyPoint();
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}

void Snake::destroyPoint()
{
	Point *pCur = pHead;
	while (pHead != NULL)
	{
		pCur = pHead->next;
		delete pHead;
		pHead = pCur;
	}
}

void Snake::addPoint(int x, int y)
{
	Point *newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	newPoint->next = NULL;
	//如果原来头不为空，那么改为身子
	if (pHead != NULL)
	{
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(hOut, pHead->y * 2, pHead->x);
		cout << '=';
	}
	//更新头部
	newPoint->next = pHead;
	pHead = newPoint;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(hOut, pHead->y * 2, pHead->x);
	cout << '@';
}

void Snake::deletePoint()
{
	//两个结点以上才去做删除操作
	if (pHead == NULL || pHead->next == NULL) return;

	Point *pCur = pHead->next;
	Point *pPre = pHead;
	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//删除尾结点
	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy(hOut, pCur->y * 2, pCur->x);
	cout << ' ';
	delete pCur;

	//???
	pCur = NULL;
	pPre->next = NULL;


}

bool Snake::move(char key)
{
	int x = pHead->x;
	int y = pHead->y;
	switch (key)
	{
	case UP:
		x--; 
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	}

	//如果下一步是尾巴，不应该死亡
	Point *pCur = pHead->next;
	Point *pPre = pHead;
	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	if (pCur->x == x && pCur->y == y)
	{
		//碰到尾巴 循环
		isrear = true;
	}
	else
	{
		//判断要到达的位置是否有效
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addPoint(x, y);
			deletePoint();
			system("cls");
			wall.drawWall();
			cout << "得分：" <<getScore() << "分" << endl;
			cout << "GAME OVER!" << endl;
			return false;
		}
	}
	//移动成功
	//1,吃到食物 2,未吃到
	if (wall.getWall(x, y) == '#')
	{
		addPoint(x, y);
		food.setFood();
	}
	else
	{
		addPoint(x, y);
		deletePoint();
		if (isrear)
		{
			wall.setWall(x, y, '@');
			gotoxy(hOut, y * 2, x);
			cout << '@';
		}
	}
	return true;
}

int Snake::
getSleepTime()
{
	int sleeptime = 0;
	int size = countList();
	if (size < 5) sleeptime = 300;
	else if (size >= 5 && size <= 8) sleeptime = 200;
	else sleeptime = 100;
	return sleeptime;
}

int Snake::countList()
{
	int size = 0;
	Point *curPoint = pHead;
	while (curPoint != NULL)
	{
		size++;
		curPoint = curPoint->next;
	}
	return size;
}

int Snake::getScore()
{
	int size = countList();
	int score = (size - 3) * 100;
	return score;
}
