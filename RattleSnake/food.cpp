#include"food.h"
#include"Windows.h"

void gotoxy2(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;             //横坐标
	pos.Y = y;            //纵坐标
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);//定义显示器句柄变量

Food::Food(Wall & tempwall):wall(tempwall)
{

}

void Food::setFood()
{
	while (true)
	{
		foodX = rand() % (Wall::ROW - 2) + 1;
		foodY = rand() % (Wall::COL - 2) + 1;
		//如果随机位置与蛇的位置重叠，则重新生成，是空格则生成
		if (wall.getWall(foodX, foodY) == ' ')
		{
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOut2, foodY * 2, foodX);
			cout << '#';	
			break;
		}
	}
}