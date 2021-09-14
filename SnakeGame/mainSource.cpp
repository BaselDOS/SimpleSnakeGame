#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool gameOver;
const int Height=20;
const int Width = 50;
int HeadX, HeadY, FruitX, FruitY, Score;
enum eDirection {STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
int TailX[100], TailY[100];
int TailLength;
int Diff;
void Setup()
{
	gameOver = false;
	dir = STOP;
	HeadX = Width / 2;
	HeadY = Height / 2;
	FruitY = rand() % Height;
	FruitX = rand() % Width;
}

void Draw()
{
	system("cls");	
	for (int i = 0; i < Width; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (j == 0)cout << "#";
			if (j == Width-1 )cout << "#";
			if (i == HeadY && j == HeadX)cout << "O";
			else if (i == FruitY && j == FruitX)cout << "$";
			else
			{
				bool trackPrint = false;
				for (int k = 0; k < TailLength; k++)
				{
					
					if (TailX[k] == j && TailY[k] == i)
					{
						cout << "o";
						trackPrint = true;
					}					
				}
				if (!trackPrint)
					cout << " ";
				
			}
		}
		cout << endl;
	}



	for (int i = 0; i < Width; i++)
		cout << "#";
	cout << endl;

	cout << "your Score is:" << Score << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':dir = LEFT;  break;
		case 's':dir = DOWN; break;
		case 'w':dir = UP; break;
		case 'd':dir = RIGHT; break;
		case 'x':gameOver = true; break;
		default: break;
		}
	}

}

void Logic(int diff)
{
	int PrevTailX = TailX[0];
	int PrevTailY = TailY[0];
	int Prev2X, Prev2Y;
	TailX[0] = HeadX;
	TailY[0] = HeadY;
	for (int i = 1; i < TailLength; i++)
	{
		Prev2X = TailX[i];
		Prev2Y = TailY[i];
		TailX[i]=PrevTailX;
		TailY[i] = PrevTailY;
		PrevTailX = Prev2X;
		PrevTailY = Prev2Y;
	}
	switch (dir)
	{	
	case LEFT:HeadX--;	break;
	case RIGHT:HeadX++;	break;
	case UP:HeadY--;break;
	case DOWN:HeadY++;break;
	default:
		break;
	}
	
	
	if (diff==1)
	{
		if (HeadX >= Width)HeadX = 0;
		else if (HeadX <= 0)HeadX = Width;
		if (HeadY >= Height)HeadY = 0;
		else if (HeadY <= 0)HeadY = Height;
	}
	if (diff==2||diff==3)
	{
		if (HeadX > Width || HeadX < 0 || HeadY<0 || HeadY>Height)gameOver = true;
	}
	
	for (int i= 0; i < TailLength; i++)
		if (TailX[i] == HeadX && TailY[i] == HeadY)gameOver = true;
	if (HeadX == FruitX && HeadY == FruitY)
	{
		Score += 10;
		FruitX = rand() % Width;
		FruitY = rand() % Height;
		TailLength++;
	}
}

void play(int diff)
{
	Setup();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic(diff);
		Sleep(10);
	}
}
void Starting()
{
	cout << "*****************************************"<<endl;
	cout << "*********Simple Snake Game***************"<<endl;
	cout << "*****************************************"<<endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "Please choose Defficulty:"<<endl;
	cout << "1.Easy"<<endl;
	cout << "2.Difficult"<<endl;
	cout << "3.Hard"<<endl;
	int Sellection;
	cin >> Sellection;
	switch (Sellection)
	{
	case 1:Diff = 1; break;
	case 2:Diff = 2; break;
	case 3:Diff = 3; break;
	default:break;
	}
	system("cls");
}
int main()
{
	Starting();
	play(Diff);
	cout << "again?(y/n)";
	char answer;
	cin >> answer;
	if (answer == 'y')
	{
		system("cls");
		Score = 0;
		TailLength = 0;
		play(Diff);
	}
	else
	{
		system("cls");
		cout << "your final score was:" << Score << endl;
		cout << "************Thank You ***************"<<endl;
		cout << "************ Good Bye ***************"<<endl;

	}


	return 1;
}