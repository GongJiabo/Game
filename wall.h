#ifndef _WALL_HEAD_
#define _WALL_HEAD_
#include<iostream>

using namespace std;

class Wall
{
public:
	enum
	{
		ROW = 26,
		COL = 26
	};
	void initWall();
	void drawWall();
	void setWall(int x, int y, char c);
	char getWall(int x, int y);
private:
	char gameArray[ROW][COL];
};

#endif