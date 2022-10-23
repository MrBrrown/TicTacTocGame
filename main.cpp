#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <vector>
#include <iostream>
#include "priorityMove.h"

using namespace std;
using namespace sf;

void DrawGrid(RenderWindow& window)
{
    Vector2u size = window.getSize();
    for (int i = 1; i < 3; i++)
    {
        RectangleShape verticalLine(Vector2f(2,size.y));//вертикальные линии
        verticalLine.setFillColor(Color::Black);
        verticalLine.move(size.x/3*i,0);
        window.draw(verticalLine);

        RectangleShape horizontalLines(Vector2f(size.x,2)); //горизонтальные линии
        horizontalLines.setFillColor(Color::Black);
        horizontalLines.move(0,size.y/3*i);
        window.draw(horizontalLines);
    }
}

void DrawX(RenderWindow& window,int x,int y)
{
    int squareSide = 200;
    RectangleShape X(Vector2f(5,sqrt(pow(squareSide,2)*2)));
    X.setFillColor(Color::Cyan);
    X.move(x,y);
    X.rotate(45);
    window.draw(X);
    X.move(-squareSide,0);
    X.rotate(-90);
    window.draw(X);
}

void DrawO(RenderWindow& window,int x,int y)
{
    int squareSide = 200;
    CircleShape O(squareSide/2.3);
    O.setOutlineThickness(3);
    O.setOutlineColor(Color::Green);
    O.move(x,y);
    window.draw(O);
}

void FillFreeSquaresVector(int gridMatrix[][3],vector<int>& turnFreePlaces, int value)
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3;j++)
            if (gridMatrix[i][j] == value)
                turnFreePlaces.push_back(i*3+j);
}

priorityMove IsMovePriority(int enemyMatrix[][3],int thisMatrix[0][3], priorityMove& move, int computerPower)
{
    int counter = 0;
    ///случай для победы по горизонтали
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (thisMatrix[i][j] == 1)
                counter++;
            if (counter == 2)
                for (int z = 0; z < 3; z++)
                    if (thisMatrix[i][z] == 0 && enemyMatrix[i][z] != 1)
                    {
                        move.x = z;
                        move.y = i;
                        if (rand()%10 + 1 <= computerPower)
                            move.isPriority = true;
                        else
                            move.isPriority = false;
                        return move;
                    }
        }
        counter = 0;
    }
    ///случай для победы по веритикали
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (thisMatrix[j][i] == 1)
                counter++;
            if (counter == 2)
                for (int z = 0; z < 3; z++)
                    if (thisMatrix[z][i] == 0 && enemyMatrix[z][i] != 1)
                    {
                        move.x = i;
                        move.y = z;
                        if (rand()%10 + 1 <= computerPower)
                            move.isPriority = true;
                        else
                            move.isPriority = false;
                        return move;
                    }
        }
        counter = 0;
    }
    ///случай для победы по главной диагонали
    for (int i = 0; i < 3; i++)
    {
        if (thisMatrix[i][i] == 1)
            counter++;
        if (counter == 2)
            for (int j = 0; j < 3; j++)
                if (thisMatrix[j][j] == 0 && enemyMatrix[j][j] != 1)
                {
                    move.x = j;
                    move.y = j;
                    if (rand()%10 + 1 <= computerPower)
                        move.isPriority = true;
                    else
                        move.isPriority = false;
                    return move;
                }
    }
    counter = 0;
    ///случай для победы по побочной диагонали
    for (int i = 0; i < 3; i++)
    {
        if (thisMatrix[i][3-1-i] == 1)
            counter++;
        if (counter == 2)
            for (int j = 0; j < 3; j++)
                if (thisMatrix[j][3-1-j] == 0 && enemyMatrix[j][3-1-j] != 1)
                {
                    move.x = 3-1-j;
                    move.y = j;
                    if (rand()%10 + 1 <= computerPower)
                        move.isPriority = true;
                    else
                        move.isPriority = false;
                    return move;
                }
    }
    counter = 0;
    //случай для блокировки горизонтальных линий оппонента
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (enemyMatrix[i][j] == 1)
                counter++;
            if (counter == 2)
                for (int z = 0; z < 3; z++)
                    if (enemyMatrix[i][z] == 0 && thisMatrix[i][z] != 1)
                    {
                        move.x = z;
                        move.y = i;
                        if (rand()%10 + 1 <= computerPower)
                            move.isPriority = true;
                        else
                            move.isPriority = false;
                        return move;
                    }
        }
        counter = 0;
    }
    //случай для блокировки веритикальных линий оппонента
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (enemyMatrix[j][i] == 1)
                counter++;
            if (counter == 2)
                for (int z = 0; z < 3; z++)
                    if (enemyMatrix[z][i] == 0 && thisMatrix[z][i] != 1)
                    {
                        move.x = i;
                        move.y = z;
                        if (rand()%10 + 1 <= computerPower)
                            move.isPriority = true;
                        else
                            move.isPriority = false;
                        return move;
                    }
        }
        counter = 0;
    }
    //случай для блокировки главной диагонали
    for (int i = 0; i < 3; i++)
    {
        if (enemyMatrix[i][i] == 1)
            counter++;
        if (counter == 2)
            for (int j = 0; j < 3; j++)
                if (enemyMatrix[j][j] == 0 && thisMatrix[j][j] != 1)
                {
                    move.x = j;
                    move.y = j;
                    if (rand()%10 + 1 <= computerPower)
                        move.isPriority = true;
                    else
                        move.isPriority = false;
                    return move;
                }
    }
    counter = 0;
    //случай для блокировки побочной диагонали
    for (int i = 0; i < 3; i++)
    {
        if (enemyMatrix[i][3-1-i] == 1)
            counter++;
        if (counter == 2)
            for (int j = 0; j < 3; j++)
                if (enemyMatrix[j][3-1-j] == 0 && thisMatrix[j][3-1-j] != 1)
                {
                    move.x = 3-1-j;
                    move.y = j;
                    if (rand()%10 + 1 <= computerPower)
                        move.isPriority = true;
                    else
                        move.isPriority = false;
                    return move;
                }
    }
    counter = 0;
}

bool CheckWin(int matrix[][3])
{
    bool isWin = false;
    if(matrix[0][0] == 1)//первая строка/главная диагональ/первый столбец
        if ((matrix[0][1] == 1 && matrix[0][2] == 1) || (matrix[1][1] == 1 && matrix[2][2] == 1) || (matrix[1][0] == 1 && matrix[2][0] == 1))
            isWin = true;
    if (matrix[0][1] == 1)//второй столец
        if (matrix[1][1] == 1 && matrix[2][1] == 1)
            isWin = true;
    if (matrix[0][2] == 1)//третий столец/побочная диагональ
        if ((matrix[1][2] == 1 && matrix[2][2] == 1)||(matrix[1][1] == 1 && matrix[2][0] == 1))
            isWin = true;
    if (matrix[1][0] == 1)//вторая строка
        if (matrix[1][1] == 1 && matrix[1][2] == 1)
            isWin = true;
    if (matrix[2][0] == 1)//третья строка
        if (matrix[2][1] == 1 && matrix[2][2] == 1)
            isWin = true;

    return isWin;
}

int main()
{
    priorityMove move;

    int playerX, playerY;    //координаты в которык игрок ствит "X"
    int freeSquares = 9;
    bool isPlayerTurn = true;
    int computerPower;

    int whatGameMode;
    cout<<"Выбирите режим игры (1 - игра с компьютером, 0 - игра искуственного интелекта)"<<endl;
    cin>>whatGameMode;
    cout<<"Вибирите силу крмпьютера (от 1 до 10)"<<endl;
    cin>>computerPower;

    RenderWindow window(VideoMode(600, 600), "Tic Tac Toe");
    window.clear(Color::White);
    DrawGrid(window);
    window.display();

    int gridMatrix [3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    int playerMatrix [3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    int opponentMatrix [3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    while (window.isOpen())
    {
        Event event{};
        while (window.pollEvent(event))
        {
            //Игрок против Компьютера
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left && whatGameMode == 1)  //получение "квадрата" клика
                {
                    if (event.mouseButton.x <= 200 && event.mouseButton.y<=200)
                        playerY = 0,playerX=0;
                    else if (event.mouseButton.x > 200 && event.mouseButton.x <= 400 && event.mouseButton.y<=200)
                        playerY = 0,playerX=1;
                    else if (event.mouseButton.x > 400 && event.mouseButton.x <= 600 && event.mouseButton.y<=200)
                        playerY = 0,playerX=2;
                    else if (event.mouseButton.x <=200 && event.mouseButton.y > 200 && event.mouseButton.y<=400)
                        playerY = 1,playerX=0;
                    else if (event.mouseButton.x > 200 && event.mouseButton.x <= 400 && event.mouseButton.y > 200 && event.mouseButton.y<=400)
                        playerY = 1,playerX=1;
                    else if (event.mouseButton.x > 400 && event.mouseButton.x <= 600 && event.mouseButton.y > 200 && event.mouseButton.y<=400)
                        playerY = 1,playerX=2;
                    else if (event.mouseButton.x <=200 && event.mouseButton.y > 400 && event.mouseButton.y<=600)
                        playerY = 2,playerX=0;
                    else if (event.mouseButton.x > 200 && event.mouseButton.x <= 400 && event.mouseButton.y > 400 && event.mouseButton.y<=600)
                        playerY = 2,playerX=1;
                    else if (event.mouseButton.x > 400 && event.mouseButton.x <= 600 && event.mouseButton.y > 400 && event.mouseButton.y<=600)
                        playerY = 2,playerX=2;

                    if (gridMatrix[playerY][playerX] == 0 && playerMatrix[playerY][playerX] == 0) //заполнение массива игрока1 (человека) для отрисовки
                    {
                        isPlayerTurn = false;
                        gridMatrix[playerY][playerX] = 1;
                        playerMatrix[playerY][playerX] = 1;
                        freeSquares--;
                    }
                    if (!isPlayerTurn && freeSquares>0)//заполнение массива игрока2 (компьютера) для отрисовки
                    {
                        move = IsMovePriority(playerMatrix, opponentMatrix, move,computerPower);
                        if (move.isPriority) //приоритетный случай (заблокировать победу опонента/выиграть)
                        {
                            gridMatrix[move.y][move.x] = 1;
                            opponentMatrix[move.y][move.x] = 1;
                            isPlayerTurn = true;
                            freeSquares--;
                            move.isPriority = false;
                        }
                        else
                        {
                            vector<int> turnFreeSqares;
                            FillFreeSquaresVector(gridMatrix,turnFreeSqares,0);//заполнение вектора свободных клеток от (0 до 8)
                            srand(time(nullptr));
                            int tmp = rand() % turnFreeSqares.size();
                            int i = turnFreeSqares[tmp]/3;         //"координата" по Y
                            int j = turnFreeSqares[tmp]%3;         //"координата" по X
                            gridMatrix[i][j] = 1;
                            opponentMatrix[i][j] = 1;
                            isPlayerTurn = true;
                            freeSquares--;
                        }
                    }

                    window.clear(Color::White);
                    DrawGrid(window);
                    for (int i = 0; i<3;i++)//отрисовка крестиков
                        for (int j = 0; j< 3; j++)
                            if (playerMatrix[i][j] == 1)
                                DrawX(window,200*(j+1),200*i);
                    for (int i = 0; i<3;i++)//отрисовка ноликов
                        for (int j = 0; j< 3; j++)
                            if (opponentMatrix[i][j] == 1)
                                DrawO(window,12 + 200*j,12+200*i);
                    window.display();

                    bool isPlayerWin = CheckWin(playerMatrix);//Проверка на победу
                    bool isComputerWin = CheckWin(opponentMatrix);
                    if (isPlayerWin)
                    {
                        sleep(seconds(2));
                        cout<<"Победа ИГРОКА";
                        return 0;
                    }
                    if (isComputerWin)
                    {
                        sleep(seconds(2));
                        cout<<"Победа КОМПЬЮТЕРА";
                        return 0;
                    }
                    else if (freeSquares == 0)
                    {
                        sleep(seconds(2));
                        cout<<"НИЧЬЯ";
                        return 0;
                    }
                }
            }

            if (event.type == Event::Closed)
                window.close();
        }
        //Игра "Искуственного Интелекта"
        if (whatGameMode == 0)
        {
            sleep(seconds(5));
            //Первый "Игрок"
            vector<int> firstPlayerVar;
            IsMovePriority(opponentMatrix,playerMatrix,move,computerPower);
            if(move.isPriority)
            {
                gridMatrix[move.y][move.x] = 1;
                playerMatrix[move.y][move.x] = 1;
                freeSquares--;
                move.isPriority = false;
            }
            else
            {
                FillFreeSquaresVector(gridMatrix,firstPlayerVar,0);
                srand(time(nullptr));
                int tmp = rand() % firstPlayerVar.size();
                int i = firstPlayerVar[tmp]/3;         //"координата" по Y
                int j = firstPlayerVar[tmp]%3;         //"координата" по X
                gridMatrix[i][j] = 1;
                playerMatrix[i][j] = 1;
                freeSquares--;
            }

            //Второй "Игрок"
            vector<int> secondPlayerVar;
            IsMovePriority(playerMatrix,opponentMatrix,move,computerPower);
            if(move.isPriority)
            {
                gridMatrix[move.y][move.x] = 1;
                opponentMatrix[move.y][move.x] = 1;
                freeSquares--;
                move.isPriority = false;
            }
            else if (freeSquares > 0)
            {
                FillFreeSquaresVector(gridMatrix,secondPlayerVar,0);
                srand(time(nullptr));
                int tmp = rand() % secondPlayerVar.size();
                int i = secondPlayerVar[tmp]/3;         //"координата" по Y
                int j = secondPlayerVar[tmp]%3;         //"координата" по X
                gridMatrix[i][j] = 1;
                opponentMatrix[i][j] = 1;
                freeSquares--;
            }

            window.clear(Color::White);
            DrawGrid(window);
            for (int i = 0; i<3;i++)//отрисовка крестиков
                for (int j = 0; j< 3; j++)
                    if (playerMatrix[i][j] == 1)
                        DrawX(window,200*(j+1),200*i);
            for (int i = 0; i<3;i++)//отрисовка ноликов
                for (int j = 0; j< 3; j++)
                    if (opponentMatrix[i][j] == 1)
                        DrawO(window,12 + 200*j,12+200*i);
            window.display();

            bool isPlayer1Win = CheckWin(playerMatrix);//Проверка на победу
            bool isPlayer2Win = CheckWin(opponentMatrix);
            if (isPlayer1Win)
            {
                sleep(seconds(2));
                cout<<"Победа ИГРОКА1 (крестики)";
                return 0;
            }
            if (isPlayer2Win)
            {
                sleep(seconds(2));
                cout<<"Победа ИГРОКА2 (нолики)";
                return 0;
            }
            else if (freeSquares == 0)
            {
                sleep(seconds(2));
                cout<<"НИЧЬЯ";
                return 0;
            }
        }
    }
    return 0;
}
