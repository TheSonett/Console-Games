// CREATED BY JOY SAHA ON 02/02/20

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;


// Variables
bool Game_Over;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int tail_len;
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN}; Direction dir;

// Functions
int setup();
int Draw();
int input();
int logic();


// main method
int main()
{
    setup();
    // Game loop
    while(!Game_Over)
    {
        Draw();
        Sleep(100);
        input();
        logic();
    }
}

int setup()
{
    Game_Over = false;
    dir = STOP;
    x = width / 2; // 20 / 2 = 10
    y = height / 2; // 20 / 2 = 10
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

int Draw()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    for(int i = 0; i < width + 2; i++)
    {
        cout << "\xB2";
    }
    cout << endl;
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            if(j == 0)
                cout << "\xB2";
            if (i == y && j == x)
                cout << "O";
            else if(i == fruitY && j == fruitX)
                cout << "\xFE";
            else
            {
                bool print = false;
                for(int k = 0; k < tail_len; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout << 'o';
                        print = true;
                    }
                }
                if(!print)
                    cout << " ";
            }

            if(j == width - 1)
                cout << "\xB2";
        }
        cout << endl;
    }
    for(int i = 0; i < width + 2; i++)
    {
        cout << "\xB2";
    }
    cout << endl;
    cout << "Score : " << score << endl;
}

int input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            Game_Over = true;
            break;
        }
    }
}

int logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < tail_len; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case DOWN:
        y++;
        break;
    case UP:
        y--;
        break;
    defaut:
        break;
    }

    /* // When the snake hits the wall, the game will be over.
    if(x > width || x < 0 || y > height || y < 0)
    {
        Game_Over = true;
    }
    */

    // When snake hits the wall, the snake will come from opposite side
    if(x >= width)
        x = 0;
    else if(x < 0)
        x = width - 1;

    if(y >= height)
        y = 0;
    else if(y < 0)
        y = height - 1;

    // When the snake eats it's self, then we have to over the game
    for(int i = 0; i < tail_len; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
        {
            Game_Over = true;
        }
    }
    //Eats the food and increase the score.
    if(x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tail_len++;
    }
}
