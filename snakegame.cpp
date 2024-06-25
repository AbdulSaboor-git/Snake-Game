#include <iostream>
#include <chrono>
#include <thread>
#include <deque>
#include <ctime>
#include <conio.h>
using namespace std;

const int boardSize = 20;
const int maxSpeed = 10;
const int minSpeed = 1;
int snakeSize = 1;
int score = 0;
string buffer[boardSize][boardSize];

//...........................CONTROLS.............................
string fruit = "o";
string snakeHead = "%";
string snakeBody = "\"";
string background = " ";
int snakeSpeed = 6;
const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
//................................................................

struct snakeSegment
{
    int x;
    int y;
};

deque<snakeSegment> snake;
int SPEED = (maxSpeed - snakeSpeed + 1) * 20;

void generateRandom(int s)
{
    srand(time(0));

    for (int i = 0; i < s; i++)
    {
        int x = rand() % (boardSize - 1);
        int y = rand() % (boardSize - 1);
        while (true)
        {
            if (buffer[x][y] == background)
            {
                buffer[x][y] = fruit;
                break;
            }
            else
            {
                x = rand() % (boardSize - 1);
                y = rand() % (boardSize - 1);
            }
        }
    }
}

void reset()
{
    snakeSize = 1;
    score = 0;
    snake.clear();
}

void initialize()
{
    reset();

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            buffer[i][j] = background;
        }
    }
    generateRandom(1);
    buffer[boardSize / 2][boardSize / 2] = snakeHead;
}

void print()
{
    string board[boardSize][boardSize];
    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            board[i][j] = buffer[i][j];
        }
    }
    string output;
    output += "Press Esc to Pause Game";
    output += "\n\n|==============================================|\n";
    output += "|\t\t    Score: " + to_string(score) + "\t\t       |\n";
    output += "|==============================================|\n";
    output += "|//////////////////////////////////////////////|\n";
    for (int i = 0; i < boardSize; i++)
    {
        output += "|/| ";
        for (int j = 0; j < boardSize; j++)
        {
            output += board[i][j] + background;
        }
        output += " |/|\n";
    }
    output += "|//////////////////////////////////////////////|\n";
    output += "|==============================================|";

    cout << output;
}

bool test(int x, int y)
{
    if (buffer[x][y] == fruit)
    {
        score++;
        snakeSize++;
        generateRandom(1);
        return false;
    }
    else if (buffer[x][y] == snakeBody)
    {
        cout << "\n\n\t   Game Over! Your Score: " << score << endl;
        chrono::milliseconds duration(2000);
        this_thread::sleep_for(duration);
        return true;
    }
    return false;
}

void visualizeSnake()
{
    bool head = false;
    for (auto &segment : snake)
    {
        if (!head)
        {
            buffer[segment.x][segment.y] = snakeHead;
            head = true;
        }
        else
            buffer[segment.x][segment.y] = snakeBody;
    }
}

void clear(int x, int y)
{
    buffer[x][y] = background;
}

void generateSnake(int x, int y)
{

    snake.push_front({x, y});
    if (snake.size() > snakeSize)
    {
        snakeSegment tail = snake.back();
        snake.pop_back();
        clear(tail.x, tail.y);
    }
}

void move(int &x, int &y, int dx, int dy)
{
    x += dx;
    y += dy;

    if (x < 0)
        x = boardSize - 1;
    else if (x >= boardSize)
        x = 0;

    if (y < 0)
        y = boardSize - 1;
    else if (y >= boardSize)
        y = 0;
}

bool isValidMove(int dx, int dy, int lastDx, int lastDy)
{
    return (dx != -lastDx || dy != -lastDy);
}

void pressAnyKeyToContinue()
{
    cout << "\nPress any key to continue...\n\n";
    _getch();
}

void speedControl()
{
    while (true)
    {

        if (snakeSpeed >= minSpeed && snakeSpeed <= maxSpeed)
        {
            char c;
            c = _getch();

            switch (c)
            {
            case 75:
                if (snakeSpeed != minSpeed)
                    snakeSpeed--;
                break;
            case 77:
                if (snakeSpeed != maxSpeed)
                    snakeSpeed++;
                break;
            case 27:
                return;
            default:
                break;
            }
        }
        SPEED = (maxSpeed - snakeSpeed + 1) * 20;

        string output = "...................... Snake Game ......................\n";
        output += "                  Snake Speed Control\n";
        output += "\nUse Arrrow Keys  <  >  to control the speed.";
        output += "\nPress Esc to go back.\n\n";
        output += "Speed [";
        for (int i = 0; i < snakeSpeed; i++)
        {
            output += "~";
        }
        for (int i = 0; i < maxSpeed - snakeSpeed; i++)
            output += " ";
        output += "]";

        system("cls");
        cout << output;
    }
}

void settings()
{
    system("cls");
    cout << "...................... Snake Game ......................\n";
    cout << "                        Settings\n";
    cout << "\n1. Snake Speed";
    cout << "\n2. Go Back\n\n";
    char c;
    c = _getch();
    switch (c)
    {
    case '1':
        speedControl();
        break;
    case '2':
        return;
    }
}

void instructions()
{
    while (true)
    {
        system("cls");
        cout << "...................... Snake Game ......................\n";
        cout << "                 Gameplay Instructions\n";

        cout << "\nKey Bindings\n";
        cout << "   Move up\t:  W \n";
        cout << "   Move Down\t:  S \n";
        cout << "   Move Left\t:  A \n";
        cout << "   Move Right\t:  D \n";

        cout << "\nPress Esc to Go Back\n\n";

        char c;
        c = _getch();

        switch (c)
        {
        case 27:
            return;
        default:
            break;
        }
    }
}

int pause()
{
    char c;
    cout << "\n\nGame Paused";
    cout << "\n\n1. Resume \n2. Quit\n";
    while (true)
    {
        c = _getch();
        switch (c)
        {
        case 27:
        case '1':
            return 0;
        case '2':
            return 1;
        default:
            break;
        }
    }
}

void start()
{
    int x = boardSize / 2;
    int y = boardSize / 2;
    int dx = 0;
    int dy = 0;
    int lastDx = 0;
    int lastDy = 0;
    char z;
    bool started = false;
    initialize();
    generateSnake(x, y);
    visualizeSnake();
    system("cls");
    print();
    z = _getch();

    while (true)
    {
        if (started)
        {

            if (test(x, y))
            {
                pressAnyKeyToContinue();
                return;
            }
            generateSnake(x, y);
            visualizeSnake();
            system("cls");
            print();

            chrono::milliseconds duration(SPEED);
            this_thread::sleep_for(duration);
        }

        int newDx = 0;
        int newDy = 0;

        while (_kbhit())
        {
            z = _getch();
            if (z == 27)
                switch (pause())
                {
                case 0:
                    break;
                case 1:
                    return;
                }
        }

        if (z == UP || z == DOWN || z == LEFT || z == RIGHT)
        {
            switch (z)
            {
            case UP:
                newDx = -1;
                break;
            case LEFT:
                newDy = -1;
                break;
            case RIGHT:
                newDy = 1;
                break;
            case DOWN:
                newDx = 1;
                break;
            }
            if (isValidMove(newDx, newDy, lastDx, lastDy))
            {
                dx = newDx;
                dy = newDy;
                started = true;
            }
        }
        move(x, y, dx, dy);
        lastDx = dx;
        lastDy = dy;

        if (_kbhit())
        {
            _getch();
        }
    }
}

int main()
{
    while (true)
    {
        system("cls");
        cout << "...................... Snake Game ......................\n";
        cout << "\n1. Start Game";
        cout << "\n2. Settings";
        cout << "\n3. Gameplay Instructions";
        cout << "\n4. Exit\n\n";
        char c;
        c = _getch();

        switch (c)
        {
        case '1':
            start();
            break;
        case '2':
            settings();
            break;
        case '3':
            instructions();
            break;
        case '4':
            cout << "\n\nExiting...\n\n";
            return 0;
        default:
            break;
        }
    }

    return 0;
}