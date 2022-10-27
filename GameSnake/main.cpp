#include <iostream>
#include <fstream>
#include"myLib.h"
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <string>
#define MAX 100
using namespace std;
//thong tin nguoi choi
string Name = "";
int score = 0;
int level = 1;
//khai bao bien, mang
int toado_x[MAX] = { 0 };
int toado_y[MAX] = { 0 };
int x_food = -1;
int y_food = -1;
int len = 5;
bool endgame = false;
bool eat = true;
//khai bao ham
void info();
int Menu();
void drawframes_0();
void drawframes_1();
void create_snake();
void playgame();
void draw_snake();
void del_snake();
void move_snake(int x, int y);
void food(int& x_food, int& y_food, bool& eat);
bool gameover(int x, int y, int toadox[], int toadoy[], int len);


int main() {
	ShowCur(0);
	drawframes_0();
	if (Menu() == 14) {
		system("cls");
		int i = 1;
		ifstream file;
		file.open("C:\\Users\\Pham Ninh\\Downloads\\banner.txt", ios_base::in); //import file thì copy đường dẫn rồi đổi \ thành \\ hoặc /
		string line;
		while (getline(file, line)) {
			gotoXY(25, i);
			cout << line << endl;
			++i;
			Sleep(30);
		}
		file.close();
		drawframes_0();
		gotoXY(45, 15);
		SetColor(4);
		cout << "Please,input your name : ";cin >> Name;
		system("cls");
		SetColor(15);
		drawframes_1();
		playgame();
	}
	int c = _getch();
	return 0;
}
//hien thi thong tin nguoi choi
int Menu() {
	int i = 1;
	ifstream file;
	file.open("C:\\Users\\Pham Ninh\\Downloads\\banner.txt", ios_base::in); //import file thì copy đường dẫn rồi đổi \ thành \\ hoặc /
	string line;
	while (getline(file, line)) {
		gotoXY(25, i);
		cout << line << endl;
		++i;
		Sleep(30);
	}
	file.close();
	int temp = 0;
	gotoXY(57, 12);
	SetColor(4);
	cout << "MENU";
	SetColor(15);
	gotoXY(53, 14);
	SetColor(3);
	cout << "1. New game";
	SetColor(15);
	gotoXY(53, 15);
	cout << "2. High score";
	gotoXY(53, 16);
	cout << "3. Exit Game";
	gotoXY(53, 14);
	while (true)
	{
		if (_kbhit())
		{

			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 72)
				{
					--temp;
					if (temp < 0) {
						temp = 2;
					}
					gotoXY(53, temp + 14);
				}
				else if (c == 80)
				{
					++temp;
					if (temp >= 3) {
						temp = 0;
					}
					gotoXY(53, temp + 14);
				}
			}
			else if (c == 13) {
				return whereY();
			}
			if (whereY() == 14) {
				SetColor(3);
				cout << "1. New game";
				SetColor(15);
				gotoXY(53, 15);
				cout << "2. High score";
				gotoXY(53, 16);
				cout << "3. Exit Game";
				gotoXY(53, 14);
			}
			else if (whereY() == 15) {
				SetColor(3);
				cout << "2. High score";
				SetColor(15);
				gotoXY(53, 14);
				cout << "1. New game";
				gotoXY(53, 16);
				cout << "3. Exit Game";
				gotoXY(53, 15);
			}
			else if (whereY() == 16) {
				SetColor(3);
				cout << "3. Exit Game";
				SetColor(15);
				gotoXY(53, 14);
				cout << "1. New game";
				gotoXY(53, 15);
				cout << "2. High score";
				gotoXY(53, 16);
			}
		}
	}
	return whereY();
}
void info() {

	gotoXY(100, 10);
	cout << "Name : " << Name;
	gotoXY(100, 11);
	cout << "Your score : " << score;
	gotoXY(100, 12);
	cout << "Level : " << level;
}
//ve menu
void drawframes_0() {
	//khung menu ben trong
	gotoXY(40, 10);
	for (int i = 0;i < 40;i++) {
		cout << "+";
	}
	gotoXY(40, 18);
	for (int i = 0; i < 41; i++)
	{
		cout << "+";
	}
	for (int i = 10; i < 18; i++)
	{
		gotoXY(40, i);
		cout << "+";
	}
	for (int i = 10; i < 18; i++)
	{
		gotoXY(80, i);
		cout << "+";
	}
}
//ve tuong bao xung quanh
void drawframes_1() {
	gotoXY(0, 5);
	for (int i = 0;i < 120;i++) {
		cout << "+";
	}
	gotoXY(0, 25);
	for (int i = 0; i < 120; i++)
	{
		cout << "+";
	}
	for (int i = 5; i < 25; i++)
	{
		gotoXY(0, i);cout << "+";
	}
	for (int i = 5; i < 25; i++)
	{
		gotoXY(99, i);cout << "+";
	}
	for (int i = 5; i < 25; i++)
	{
		gotoXY(119, i);cout << "+";
	}
}
// chay game
void playgame() {
	create_snake();
	int x = toado_x[0];
	int y = toado_y[0];
	int check = 2;
	while (true)
	{
		info();
		gotoXY(toado_x[len], toado_y[len]);
		cout << " ";
		draw_snake();
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 72 && check != 0)
				{
					check = 1;
				}
				else if (c == 80 && check != 1)
				{
					check = 0;
				}
				else if (c == 75 && check != 2)
				{
					check = 3;
				}
				else if (c == 77 && check != 3)
				{
					check = 2;
				}
			}
			else if (c == 27) break;
		}
		//------ di chuyển ---
		if (check == 0)
		{
			y++;
		}
		else if (check == 1)
		{
			y--;
		}
		else if (check == 2)
		{
			x++;
		}
		else if (check == 3)
		{
			x--;
		}
		move_snake(x, y);
		food(x_food, y_food, eat);
		if (x == x_food && y == y_food) {
			len++;
			score += 10;
			eat = true;
			if (score % 100 == 0 && score >= 100)
			{
				++level;
			}
		}
		gotoXY(x, y);
		//di xuyen tuong
		if (x == 1) {
			x = 98;
		}
		else if (x == 98) {
			x = 1;
		}
		else if (y == 24 && check == 0) {
			y = 5;
		}
		else if (y == 6 && check == 1) {
			y = 25;
		}
		if (!gameover(x, y, toado_x, toado_y, len)) {
			del_snake();
			SetColor(4);
			gotoXY(50, 12);
			cout << "GAME OVER!!!";
			SetColor(0);
			break;
		}
		Sleep(100);
	}

}
void create_snake() {
	int x_firts = 60;
	int y_firts = 15;
	for (int i = 0; i < len; i++)
	{
		toado_x[i] = x_firts--;
		toado_y[i] = y_firts;
	}
}
void draw_snake() {
	for (int i = 0; i < len; i++)
	{
		gotoXY(toado_x[i], toado_y[i]);
		if (i == 0) {
			cout << "x";
		}
		else
		{
			cout << "o";
		}
	}
}
void move_snake(int x, int y)
{
	//them x,y vao dau toadox,toadoy
	for (int i = len;i > 0;i--)
	{
		toado_x[i] = toado_x[i - 1];
		toado_y[i] = toado_y[i - 1];
	}
	toado_x[0] = x;
	toado_y[0] = y;
}
void food(int& x_food, int& y_food, bool& eat) {
	if (eat) {
		x_food = random(1, 99);
		y_food = random(6, 24);
		gotoXY(x_food, y_food);
		cout << "$";
		eat = false;
	}
}
bool gameover(int x, int y, int toadox[], int toadoy[], int len) {
	for (int i = 1;i < len;i++)
	{
		if (toadox[i] == x && toadoy[i] == y) {
			return false;
		}
	}
	return true;
}
void del_snake() {
	for (int i = 0; i < len; i++)
	{
		gotoXY(toado_x[i], toado_y[i]);
		cout << " ";
	}
}