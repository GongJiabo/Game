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
	//添加随机数种子
	srand((unsigned int)time(NULL));

	//死亡标志
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
	cout << "得分：" << snake.getScore() << "分" << endl;

	
	//接收用户输入
	while (!isDead)
	{
		char key = _getch();
		//判断第一次按左 不能激活游戏
		if (preKey==NULL && key == snake.LEFT) continue;
		do
		{
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				//判断冲突按键，本次按键是否与上次冲突
				if ((key == snake.LEFT && preKey == snake.RIGHT) ||
					(key == snake.RIGHT && preKey == snake.LEFT) ||
					(key == snake.UP && preKey == snake.DOWN) ||
					(key == snake.DOWN && preKey == snake.UP))
					key = preKey;
				else preKey = key;

				if (snake.move(key) && !isDead)
				{
					//成功
					//system("cls");
					//wall.drawWall();
					gotoxy(hOut, 0, Wall::ROW);
					cout << "得分：" << snake.getScore() << "分" << endl;
					Sleep(snake.getSleepTime());
				}
				else
				{
					isDead = true;
					break;
				}
			}
			//将错误按键归正为上次移动的方向		
			else key = preKey;
		} while (!_kbhit());//当没有键盘输入时 返回0

		//if (snake.move(key) && !isDead)
		//{
		//	//成功
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