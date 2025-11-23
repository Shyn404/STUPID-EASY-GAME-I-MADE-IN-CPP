#include<iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>

bool Exit = false;
bool lineCheck = true;
int PlayerPos = 10, r, r2, Score, Life = 3, bonus;
std::string line(20, '-');
std::string line2(20, '-');

void Input()
{
	if (lineCheck)
		line[PlayerPos] = '*';
	else
		line2[PlayerPos] = '*';
	if(_kbhit())
		switch (_getch())
		{
		case'a':
			if (lineCheck)
			{
				PlayerPos--;
				line[PlayerPos + 1] = '-';
			}
			else
			{
				PlayerPos--;
				line2[PlayerPos + 1] = '-';
			}
			break;
		case'd':
			if (lineCheck)
			{
				PlayerPos++;
				line[PlayerPos - 1] = '-';
			}
			else
			{
				PlayerPos++;
				line2[PlayerPos - 1] = '-';
			}
			break;
		case's':
			lineCheck = false;
			line2[PlayerPos] = '*';
			line[PlayerPos] = '-';
			break;
		case'w':
			lineCheck = true;
			line[PlayerPos] = '*';
			line2[PlayerPos] = '-';
			break;
		}
	if (PlayerPos < 0)
		PlayerPos = 19;
	if (PlayerPos > 19)
		PlayerPos = 0;
}
void Display()
{
	std::cout << line << std::endl << line2;
	if(Score > 0)
	printf("\nScore:%d",Score);
	std::cout << std::endl;
	for (int i = 1; i <= Life; i++)
		std::cout << "<3 ";
}
void Logic()
{
	std::string& CurrentLine = lineCheck ? line : line2;
	line[r] = '&';
	line[r2] = 'X';
	if (CurrentLine[PlayerPos] == '&')
	{
			r = rand() % 19;
			Score += 15;
			CurrentLine[r] = '&';
	}
	if (CurrentLine[PlayerPos] == 'X')
	{
			r2 = rand() % 19;
			Life--;
			CurrentLine[r2] = 'X';
	}
	if (Life == 0)
		Exit = true;
	for (size_t i = 0; i < line.size(); i++)
		if (i != r && line[i] == '&')
			line[i] = '-';
	for (size_t i = 0; i < line.size(); i++)
		if (i != r2 && line[i] == 'X')
			line[i] = '-';
	for (size_t i = 0; i < line2.size(); i++)
		if (i != r && line2[i] == '&')
			line2[i] = '-';
	for (size_t i = 0; i < line2.size(); i++)
		if (i != r2 && line2[i] == 'X')
			line2[i] = '-';
}
void GameOver()
{
	system("cls");
	system("color 04");
	std::cout << ".1 Retry\n.2 Exit\n:";
}

int main()
{
	std::srand(time(0));
	 r = rand() % 20;
	 r2 = rand() % 20;
	 system("color 0A");
	 while (true)
	 {
		 while (!Exit)
		 {
			 system("cls");
			 Display();
			 Logic();
			 Input();
		 }
		 if (Exit)
		 {
			 GameOver();
			 int Choice;
			 std::cin >> Choice;
			 switch (Choice)
			 {
			 case 1:
				 system("color 0A");
				 Life = 3;
				 Score = 0;
				 Exit = false;
				 continue;
			 case 2:
				 return 0;
				 break;
			 default:
				 std::cout << "\ninvalid input Only 1 - 2!";
				 std::cin >> Choice;
				 break;
			 }
		 }
	 }
	return 0;
}
