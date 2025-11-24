#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>

const int WIDTH = 20;
const int MAX_LIFE = 3;

// Game state
bool ExitGame = false;
int PlayerPos = 10, Score = 0, Life = MAX_LIFE;
bool PlayerTopLine = true;
enum Direction { UP, DOWN, LEFT, RIGHT, NONE, BONUS };
Direction CurrentMove = NONE;

// Objects
struct Object {
    int pos;
    bool onTop;  // true = top line, false = bottom line
    char symbol;
};

Object bonus;
Object obstacle;

// Initialize objects
void initObjects() {
    bonus.pos = rand() % WIDTH;
    bonus.onTop = true;
    bonus.symbol = '&';

    // Make sure obstacle does not overlap bonus initially
    do {
        obstacle.pos = rand() % WIDTH;
    } while (obstacle.pos == bonus.pos);

    obstacle.onTop = true;
    obstacle.symbol = 'X';
}

// Get player input
Direction GetDirection() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': return UP;
            case 's': return DOWN;
            case 'a': return LEFT;
            case 'd': return RIGHT;
            case 'e': return BONUS;
        }
    }
    return NONE;
}

// Handle player movement and input
void Input() {
    Direction dir = GetDirection();

    if (dir == LEFT || dir == RIGHT)
        CurrentMove = dir;

    if (dir == BONUS && Score >= 500 && Life < MAX_LIFE) {
        Score -= 500;
        Life++;
    }

    if (dir == UP) PlayerTopLine = true;
    if (dir == DOWN) PlayerTopLine = false;

    // Move horizontally
    switch (CurrentMove) {
        case LEFT: PlayerPos--; break;
        case RIGHT: PlayerPos++; break;
        default: break;
    }

    // Wrap horizontally
    if (PlayerPos < 0) PlayerPos = WIDTH - 1;
    if (PlayerPos >= WIDTH) PlayerPos = 0;
}

// Update game logic and collisions
void Logic() {
    // Fall objects from top → bottom
    if (bonus.onTop) bonus.onTop = false;
    if (obstacle.onTop) obstacle.onTop = false;

    // Collision check
    Object* objects[] = { &bonus, &obstacle };
    for (Object* obj : objects) {
        if (obj->pos == PlayerPos &&
            ((obj->onTop && PlayerTopLine) || (!obj->onTop && !PlayerTopLine))) {

            if (obj->symbol == '&') {
                Score += 100;

                // respawn at top at a new position not overlapping obstacle
                int newPos;
                do {
                    newPos = rand() % WIDTH;
                } while (newPos == obstacle.pos);
                obj->pos = newPos;
                obj->onTop = true;

            } else if (obj->symbol == 'X') {
                Life--; // decrement immediately
                if (Life < 0) Life = 0;

                // respawn at top at a new position not overlapping bonus
                int newPos;
                do {
                    newPos = rand() % WIDTH;
                } while (newPos == bonus.pos);
                obj->pos = newPos;
                obj->onTop = true;

                if (Life <= 0) ExitGame = true;
            }
        }
    }
}

// Render frame using double buffer with colors
void Display() {
    // Move cursor home for smooth update
    std::cout << "\033[H";

    // Top line
    for (int i = 0; i < WIDTH; i++) {
        if (PlayerTopLine && i == PlayerPos)
            std::cout << "\033[33m*\033[0m"; // yellow player
        else if (bonus.onTop && i == bonus.pos)
            std::cout << "\033[32m&\033[0m"; // green bonus
        else if (obstacle.onTop && i == obstacle.pos)
            std::cout << "\033[31mX\033[0m"; // red obstacle
        else
            std::cout << "\033[37m-\033[0m"; // white empty
    }
    std::cout << "\n";

    // Bottom line
    for (int i = 0; i < WIDTH; i++) {
        if (!PlayerTopLine && i == PlayerPos)
            std::cout << "\033[33m*\033[0m"; // yellow player
        else if (!bonus.onTop && i == bonus.pos)
            std::cout << "\033[32m&\033[0m"; // green bonus
        else if (!obstacle.onTop && i == obstacle.pos)
            std::cout << "\033[31mX\033[0m"; // red obstacle
        else
            std::cout << "\033[37m-\033[0m"; // white empty
    }
    std::cout << "\n";

    // Score
    std::cout << "\033[32mScore: " << Score << "\033[0m\n";

    // Life hearts (dynamic)
    std::cout << "\033[31m";
    for (int i = 0; i < Life; i++) std::cout << "<3 ";
    std::cout << "\033[0m\n";
}

void GameOver() {
    system("cls");
    system("color 04");
    std::cout << "Game Over!\n1. Retry\n2. Exit\n:";
}

int main() {
    srand((unsigned int)time(0));
    initObjects();

    // Reserve space for smooth updates
    std::cout << std::string(5, '\n');

    while (true) {
        ExitGame = false;
        PlayerPos = 10;
        PlayerTopLine = true;
        Score = 0;
        Life = MAX_LIFE;
        CurrentMove = NONE;
        initObjects();

        while (!ExitGame) {
            Display();  // render frame
            Logic();    // update objects and collisions
            Input();    // get player input
            Sleep(50);  // faster frame speed
        }

        GameOver();
        int choice;
        std::cin >> choice;
        if (choice == 2) break;
        system("cls");
    }

    return 0;
}
