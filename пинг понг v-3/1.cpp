#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

using namespace std;

class Paddle {
private:
    int x, y;
public:
    Paddle(int startX, int startY) {
        x = startX;
        y = startY;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void moveUp() {
        if (y > 0) {
            y--;
        }
    }

    void moveDown() {
        if (y < 19) {
            y++;
        }
    }
};

class Ball {
private:
    int x, y;
    int directionX, directionY;
public:
    Ball(int startX, int startY) {
        x = startX;
        y = startY;
        directionX = -1;
        directionY = -1;
    }

    void update() {
        x += directionX;
        y += directionY;

        if (x == 0 || x == 39) { // Границы поля
            directionX *= -1;
        }

        if (y == 0 || y == 19) { // Границы поля
            directionY *= -1;
        }
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void changeDirectionX() {
        directionX *= -1;
    }

    void changeDirectionY() {
        directionY *= -1;
    }
};

class Game {
private:
    Paddle* player1;
    Paddle* player2;
    Ball* ball;
    int score1;
    int score2;

public:
    Game() {
        player1 = new Paddle(1, 9);
        player2 = new Paddle(38, 9);
        ball = new Ball(20, 10);
        score1 = 0;
        score2 = 0;
    }

    ~Game() {
        delete player1;
        delete player2;
        delete ball;
    }

    void draw() {
        system("cls");

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 40; j++) {
                if (i == 0 || i == 19 || j == 0 || j == 39) {
                    cout << char(219); // Границы поля
                }
                else if (j == ball->getX() && i == ball->getY()) {
                    cout << char(220); // Мяч
                }
                else if (j == player1->getX() && i == player1->getY()) {
                    cout << char(222); // Игрок 1
                }
                else if (j == player2->getX() && i == player2->getY()) {
                    cout << char(221); // Игрок 2
                }
                else {
                    cout << " ";
                }
            }
            cout << endl;
        }

    }
    void update() {
        ball->update();

        if (ball->getX() == player1->getX() + 1 && ball->getY() >= player1->getY() && ball->getY() <= player1->getY() + 3) {
            ball->changeDirectionX();
        }

        if (ball->getX() == player2->getX() - 1 && ball->getY() >= player2->getY() && ball->getY() <= player2->getY() + 3) {
            ball->changeDirectionX();
        }
    }

    void getInput() {
        if (_kbhit()) {
            char key = _getch();

            switch (key) {
            case 'w':
                player1->moveUp();
                break;
            case 's':
                player1->moveDown();
                break;
            case 'i':
                player2->moveUp();
                break;
            case 'k':
                player2->moveDown();
                break;
            }
        }
    }
    bool isGameOver() {
            if (ball->getX() == 0 || ball->getX() == 39) { // мяч достиг границы поля
                return true;
            }

            return false;
        }
    };
    int main() {
        Game game;

        while (true) {
            game.draw();
            game.update();
            game.getInput();

            if (game.isGameOver()) {
                break;
            }

            Sleep(100); // Задержка для плавности игры
        }
        setlocale(LC_ALL, "RUS");
        cout << "Игра окончена!" << endl;
        system("pause");

        return 0;
    }
