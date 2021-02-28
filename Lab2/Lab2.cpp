#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
using namespace std;

struct Player
{
    int coordX;
    int coordY;
    int score;

};

enum Directions
{
    Up,
    Down,
    Right,
    Left
};

void drawMap(int map[20][20], Player player) 
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (map[i][j] == 1)
            {
                cout << char(177);
                cout << char(177);
            }
            if (map[i][j] == 0)
            {
                cout << "  ";
            }
            if (map[i][j] == 2)
            {
                cout << "! ";
            }
            if (map[i][j] == 3)
            {
                cout << "# ";
            }
        }
        cout << endl;
    }
    cout << "\nScore: " << player.score;
}

bool isOnSpecifiedSlot(int map[20][20], int x,  int y, int slotNum) 
{
    if (map[y][x] == slotNum)
        return true;
    else
        return false;
}

void setApples(int(&map)[20][20]) 
{
    int applesCount = 0;
    while (applesCount < 4)
    {
        int x = rand() % 19 + 1;
        int y = rand() % 19 + 1;
        if (isOnSpecifiedSlot(map, x, y, 0))
        {
            map[y][x] = 2;
            applesCount++;
        }      
    }
}

void eatApple(int(&map)[20][20], Player& player)
{
    if (isOnSpecifiedSlot(map, player.coordX, player.coordY, 2))
    {
        map[player.coordY][player.coordX] = 0;
        player.score++;
    }
}

bool canMove(int map[20][20], int x, int y, Directions direction)
{
    bool move = false;
    switch (direction)
    {
        case Up:
            if (map[y - 1][x] != 1)
                move = true;
            break;
        case Down:
            if (map[y + 1][x] != 1)
                move = true;
            break;
        case Right:
            if (map[y][x + 1] != 1)
                move = true;
            break;
        case Left:
            if (map[y][x - 1] != 1)
                move = true;
            break;
    }

    return move;
}

bool endGame(Player player)
{
    if (player.coordY == 19 && player.coordX == 18)
        return true;
    else
        return false;
}

void movePlayer(int(&map)[20][20], Player& player)
{
    map[player.coordY][player.coordX] = 0;

    bool isStop = false;
    while (!isStop) {
        switch (_getch()) {
        case 'd':
            if (canMove(map, player.coordX, player.coordY, Right))
                player.coordX++;
            isStop = true;
            break;
        case 'a':
            if (canMove(map, player.coordX, player.coordY, Left))
                player.coordX--;
            isStop = true; 
            break;
        case 'w':
            if (canMove(map, player.coordX, player.coordY, Up))
                player.coordY--;
            isStop = true;
            break;
        case 's':
            if (canMove(map, player.coordX, player.coordY, Down))
                player.coordY++;
            isStop = true;
            break;
        }
    }
    eatApple(map, player);
    map[player.coordY][player.coordX] = 3;
}

int main()
{
    srand(time(NULL));

    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle, &structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(handle, &structCursorInfo);

    int map[20][20] = { {1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
                        {1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,},
                        {1,0,1,1,0,1,1,1,0,0,0,0,1,0,1,1,0,0,1,1,},
                        {1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,1,1,1,},
                        {1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,},
                        {1,1,0,0,0,1,0,1,1,1,0,1,1,1,1,0,0,0,0,1,},
                        {1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,1,},
                        {1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0,0,0,0,1,},
                        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,1,1,},
                        {1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,},
                        {1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,0,1,},
                        {1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,0,0,0,1,},
                        {1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,},
                        {1,0,1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,1,},
                        {1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,},
                        {1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,},
                        {1,0,1,0,1,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,},
                        {1,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,1,},
                        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,1,},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,} };

    Player player;
    player.coordX = 1;
    player.coordY = 0;
    player.score = 0;

    setApples(map);

    while (endGame(player) == false)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
        drawMap(map, player);
        movePlayer(map, player);  
    }
    
    system("cls");
    cout << " Victory!\n Score: " << player.score;

    int _; cin >> _;
    return 0;
}

