#include <iostream>
#include <string>
#include <conio.h>
#include <ctime>
#define _CRT_SECURE_NO_WARNINGS

bool Exit = false;
int size = 20, PlayerPos, Score, Life = 3;
std::string line(20, '-');

void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'a':
			PlayerPos--;
			line[PlayerPos + 1] = '-';
			if (PlayerPos <= 0)
				PlayerPos = 19;
			break;
		case'd':
			PlayerPos++;
			line[PlayerPos - 1] = '-';
			if (PlayerPos >= 20)
				PlayerPos = 0;
			break;
		case'x':
			Exit = true;
			break;

		}
	}
}
void display()
{
	system("color 0A");
	std::srand(time(0));
	system("cls");
	std::cout << line;
	line[PlayerPos] = '*';
	int r = rand() % 19;
	int r2 = rand() % 19;
	line[r] = '&';
	line[r2] = 'X';
	for (size_t i = 0; i <= line.size(); i++)
		if (i != r && line[i] == '&')
			line[i] = '-';
	for (size_t i = 0; i <= line.size(); i++)
		if (i != r2 && line[i] == 'X')
			line[i] = '-';
	if (PlayerPos == r || PlayerPos == r2)
	{
		if (PlayerPos == r)
		{
			line[r] = '-';
			line[PlayerPos] = '*';
			r = rand() % 19;
			Score += 15;
		}
		else
		{
			line[r2] = '-';
			line[PlayerPos] = '*';
			r2 = rand() % 19;
			Life--;
		}
	}
	else
		line[r] = '&';
	if (Score >= 0)
		printf("\n\nScore:%d", Score);
	else if (Score < 0)
		Score = 0;
	std::cout << std::endl;
	for (int i = 1; i <= Life; i++)
		std::cout << '$';
	if (Life <= 0)
		Exit = true;
}
void GameOver()
{
	system("cls");
	system("color 04");
	std::cout << "GameOver\n";
	system("pause");
	system("cls");
	std::cout << ".1Play\n.2Exit\n";
}

int main()
{
	while (true)
	{
		while (!Exit)
		{
			display();
			input();
		}
		if (Exit)
		{
			GameOver();
			int choice;
			std::cin >> choice;
			switch (choice)
			{
			case 1:
				Exit = false;
				Score = 0;
				Life = 3;
				continue;
				
			case 2:
				system("cls");
				std::cout << "SIKE\n";
				system("pause");
				system("cls");
				Exit = false;
				Score = 0;
				Life = 3;
				continue;
			}
		}
	}
      return 0;
}