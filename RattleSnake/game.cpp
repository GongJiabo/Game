#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
#include"wall.h"
#include"snake.h"
#include"food.h"
using namespace std;

int main()
{
	//������������
	srand((unsigned int)time(NULL));

	//������־
	bool isDead = false;

	char preKey = NULL;

	Wall wall;
	wall.initWall();
	wall.drawWall();

	Food food(wall);
	food.setFood();

	Snake snake(wall,food);
	snake.initSnake();

	gotoxy(hOut, 0, Wall::ROW);
	cout << "�÷֣�" << snake.getScore() << "��" << endl;

	
	//�����û�����
	while (!isDead)
	{
		char key = _getch();
		//�жϵ�һ�ΰ��� ���ܼ�����Ϸ
		if (preKey==NULL && key == snake.LEFT) continue;
		do
		{
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				//�жϳ�ͻ���������ΰ����Ƿ����ϴγ�ͻ
				if ((key == snake.LEFT && preKey == snake.RIGHT) ||
					(key == snake.RIGHT && preKey == snake.LEFT) ||
					(key == snake.UP && preKey == snake.DOWN) ||
					(key == snake.DOWN && preKey == snake.UP))
					key = preKey;
				else preKey = key;

				if (snake.move(key) && !isDead)
				{
					//�ɹ�
					//system("cls");
					//wall.drawWall();
					gotoxy(hOut, 0, Wall::ROW);
					cout << "�÷֣�" << snake.getScore() << "��" << endl;
					Sleep(snake.getSleepTime());
				}
				else
				{
					isDead = true;
					break;
				}
			}
			//�����󰴼�����Ϊ�ϴ��ƶ��ķ���		
			else key = preKey;
		} while (!_kbhit());//��û�м�������ʱ ����0

		//if (snake.move(key) && !isDead)
		//{
		//	//�ɹ�
		//	system("cls");
		//	wall.drawWall();
		//	Sleep(snake.getSleepTime());
		//}
		//else
		//{
		//	isDead = true;
		//	break;
		//}
	}
	system("pause");
	return EXIT_SUCCESS;
}