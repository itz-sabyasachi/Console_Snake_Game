#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

class Snake {
private:
    vector<pair<int, int>> body;
    int direction;
    int score;

public:
    Snake(int w, int h);
    void move();
    void grow();
    void change_direction();
    int get_score();
    vector<pair<int, int>>& get_body();
};

Snake::Snake(int w, int h) {
    body.push_back({ w / 2, h / 2 });
    body.push_back({ w / 2 + 1, h / 2 });
    body.push_back({ w / 2 + 2, h / 2 });
    direction = 3;
    score = 0;
}

void Snake::change_direction() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'w': if (direction != 2) direction = 1;
            break;
        case 's': if (direction != 1) direction = 2;
            break;
        case 'a': if (direction != 4) direction = 3;
            break;
        case 'd': if (direction != 3) direction = 4;
            break;
        }
    }
}

void Snake::move() {
    if (direction == 0) return;

    auto head = body.front();
    int new_x = head.first, new_y = head.second;

    switch (direction) {
    case 1: new_y--; 
        break;
    case 2: new_y++;
        break;
    case 3: new_x--;
        break;
    case 4: new_x++; 
        break;
    }

    body.insert(body.begin(), { new_x, new_y });
}

void Snake::grow() {
    score = score + 10;
}

int Snake::get_score() {
    return score;
}

vector<pair<int, int>>& Snake::get_body() {
    return body;
}

class Game {
private:
    Snake snake;
    pair<int, int> food;
    const int width = 40;
    const int height = 20;

    void reset_game() {
        snake = Snake(width, height);
        generate_food();
    }

public:
    Game();
    void run();
    void draw();
    void generate_food();
    bool is_collision();
    bool food_eaten();
};

Game::Game() : snake(width, height) {
    srand(time(0));
    generate_food();
}

void Game::generate_food() {
    while (true) {
        int x = rand() % (width - 2) + 1;
        int y = rand() % (height - 2) + 1;

        bool on_snake = false;
        for (auto segment : snake.get_body()) {
            if (segment.first == x && segment.second == y) {
                on_snake = true;
                break;
            }
        }

        if (!on_snake) {
            food = { x, y };
            break;
        }
    }
}

void Game::draw() {
    system("cls");

    // Top border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Game grid
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || x == width - 1) cout << "#";

            if (x == food.first && y == food.second) cout << "*";
            else {
                bool is_snake = false;
                for (auto segment : snake.get_body()) {
                    if (segment.first == x && segment.second == y) {
                        cout << (segment == snake.get_body().front() ? "O" : "o");
                        is_snake = true;
                        break;
                    }
                }
                if (!is_snake) cout << " ";
            }
        }
        cout << endl;
    }

    // Bottom border
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\nScore: " << snake.get_score() << endl;
}

bool Game::food_eaten() {
    auto head = snake.get_body().front();
    return (head.first == food.first && head.second == food.second);
}

bool Game::is_collision() {
    auto head = snake.get_body().front();

    // Wall collision
    if (head.first <= 0 || head.first >= width - 1 || head.second < 0 || head.second >= height) {
        return true;
    }

    // Self collision
    auto& body = snake.get_body();
    for (size_t i = 1; i < body.size(); i++) {
        if (head == body[i]) return true;
    }

    return false;
}

void Game::run() {
    while (true) {
        draw();
        snake.change_direction();
        snake.move();

        if (food_eaten()) {
            snake.grow();
            generate_food();
        }
        else {
            if (snake.get_body().size() > 1) {
                snake.get_body().pop_back();
            }
        }

        if (is_collision()) {
            system("cls");
            cout << "GAME OVER! Final Score: " << snake.get_score() << endl;
            cout << "Press 'R' to restart or any key to exit.\n";
            char input = _getch();
            if (input == 'r' || input == 'R') {
                reset_game();
            }
            else {
                break;
            }
        }

        Sleep(120);
    }
}

int main() {
    Game game;
    game.run();
    return 0;
}