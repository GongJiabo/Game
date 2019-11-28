#include "snake.h"
#include<Windows.h>

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;             //������
	pos.Y = y;            //������
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//������ʾ���������

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
	//���ԭ��ͷ��Ϊ�գ���ô��Ϊ����
	if (pHead != NULL)
	{
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy(hOut, pHead->y * 2, pHead->x);
		cout << '=';
	}
	//����ͷ��
	newPoint->next = pHead;
	pHead = newPoint;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy(hOut, pHead->y * 2, pHead->x);
	cout << '@';
}

void Snake::deletePoint()
{
	//����������ϲ�ȥ��ɾ������
	if (pHead == NULL || pHead->next == NULL) return;

	Point *pCur = pHead->next;
	Point *pPre = pHead;
	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//ɾ��β���
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

	//�����һ����β�ͣ���Ӧ������
	Point *pCur = pHead->next;
	Point *pPre = pHead;
	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	if (pCur->x == x && pCur->y == y)
	{
		//����β�� ѭ��
		isrear = true;
	}
	else
	{
		//�ж�Ҫ�����λ���Ƿ���Ч
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addPoint(x, y);
			deletePoint();
			system("cls");
			wall.drawWall();
			cout << "�÷֣�" <<getScore() << "��" << endl;
			cout << "GAME OVER!" << endl;
			return false;
		}
	}
	//�ƶ��ɹ�
	//1,�Ե�ʳ�� 2,δ�Ե�
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
