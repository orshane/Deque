# Deque
A deque function for c. This deque header can be used to make fixed size deque.This is useful for games and other purposes. Don't forget to put the library in the include folder. 

```                                ===Example Usage===
#include <stdio.h>
#include <deque.h>

DECLARE_STACK_DEQUE(int ,deque , 10);

int main() {
deque d;
deque_init(&d);

deque_push_back(&d, 10);
deque_push_back(&d, 20);
deque_push_back(&d, 30);

for (size_t i = 0; i < deque_size(&d); i++) {
    int *val = deque_element(&d, i);
    if (val) printf("%d ", *val);
}
printf("\n");
   return 0;
}
```

Snake game using the deque header and raylib

```c
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>
#include <deque.h>

#define CELL_SIZE 35
#define CELL_COUNT 20

Color Green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

// Declare a deque of Vector2 with capacity 128
DECLARE_STACK_DEQUE(Vector2, Vector2Deque, 128)

double lastUpdateTime = 0;

// Utilities
bool elementInDeque(Vector2 element, Vector2Deque *deque) {
    for (size_t i = 0; i < Vector2Deque_size(deque); i++) {
        Vector2 *v = Vector2Deque_element(deque, i);
        if (v && Vector2Equals(*v, element)) return true;
    }
    return false;
}

bool eventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

// Snake struct
typedef struct {
    Vector2Deque body;
    Vector2 direction;
    bool addSegment;
} Snake;

void Snake_init(Snake *snake) {
    Vector2Deque_init(&snake->body);
    Vector2Deque_push_back(&snake->body, (Vector2){6, 9});
    Vector2Deque_push_back(&snake->body, (Vector2){5, 9});
    Vector2Deque_push_back(&snake->body, (Vector2){4, 9});
    snake->direction = (Vector2){1, 0};
    snake->addSegment = false;
}

void Snake_draw(Snake *snake) {
    for (size_t i = 0; i < Vector2Deque_size(&snake->body); i++) {
        Vector2 *v = Vector2Deque_element(&snake->body, i);
        Rectangle segment = {v->x * CELL_SIZE, v->y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
        DrawRectangleRounded(segment, 0.5, 6, darkGreen);
    }
}

void Snake_update(Snake *snake) {
    Vector2 *head = Vector2Deque_element(&snake->body, 0);
    Vector2 newHead = Vector2Add(*head, snake->direction);

    Vector2Deque_push_front(&snake->body, newHead);
    if (!snake->addSegment) {
        Vector2 trash;
        Vector2Deque_pop_back(&snake->body, &trash);
    } else {
        snake->addSegment = false;
    }
}

// Food struct
typedef struct {
    Vector2 position;
    Texture2D texture;
} Food;

Vector2 GenerateRandomCell() {
    return (Vector2){ GetRandomValue(0, CELL_COUNT - 1), GetRandomValue(0, CELL_COUNT - 1) };
}

Vector2 GenerateRandomPos(Vector2Deque *snakeBody) {
    Vector2 pos = GenerateRandomCell();
    while (elementInDeque(pos, snakeBody)) {
        pos = GenerateRandomCell();
    }
    return pos;
}

void Food_init(Food *food, Vector2Deque *snakeBody) {
    Image image = LoadImage("/home/user/Snakeinc/res/food.png");
    food->texture = LoadTextureFromImage(image);
    UnloadImage(image);
    food->position = GenerateRandomPos(snakeBody);
}

void Food_unload(Food *food) {
    UnloadTexture(food->texture);
}

void Food_draw(Food *food) {
    DrawTexture(food->texture, food->position.x * CELL_SIZE, food->position.y * CELL_SIZE, WHITE);
}

// Game struct
typedef struct {
    Snake snake;
    Food food;
} Game;

void Game_init(Game *game) {
    Snake_init(&game->snake);
    Food_init(&game->food, &game->snake.body);
}

void Game_checkCollisionWithFood(Game *game) {
    Vector2 *head = Vector2Deque_element(&game->snake.body, 0);
    if (Vector2Equals(*head, game->food.position)) {
        game->food.position = GenerateRandomPos(&game->snake.body);
        game->snake.addSegment = true;
    }
}

void Game_update(Game *game) {
    Snake_update(&game->snake);
    Game_checkCollisionWithFood(game);
}

void Game_draw(Game *game) {
    Food_draw(&game->food);
    Snake_draw(&game->snake);
}

// Main
int main(void) {
    InitWindow(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT, "SnakeInc");
    SetTargetFPS(60);

    Game game;
    Game_init(&game);

    while (!WindowShouldClose()) {
        if (eventTriggered(0.2)) {
            Game_update(&game);
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = (Vector2){0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = (Vector2){0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = (Vector2){-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = (Vector2){1, 0};
        }

        BeginDrawing();
        ClearBackground(Green);
        Game_draw(&game);
        EndDrawing();
    }

    Food_unload(&game.food);
    CloseWindow();
    return 0;
}
```
