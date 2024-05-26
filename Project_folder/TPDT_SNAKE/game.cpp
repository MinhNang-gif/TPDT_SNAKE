#include "game.h"
#include"dohoa.h"
#include <chrono>
#include <thread>
#include <iostream>
#include "SDL.h"

game::game(std::size_t grid_width, std::size_t grid_height, float speed)
    : snake(grid_width, grid_height, speed),
    grid_width(grid_width),
    grid_height(grid_height),
    engine(dev()),
    random_w(0, static_cast<int>(grid_width - 1)),
    random_h(0, static_cast<int>(grid_height - 1)) {
    PlaceFood();
}
void game::Run(dieukhien const& controller, dohoa& renderer, std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;
    while (running) {
        frame_start = SDL_GetTicks();
        controller.HandleInput(running, snake);
        Update();
        if (!snake.alive) {
            SDL_Delay(300);
            renderer.GameOverScreen();
            SDL_Delay(700);
            renderer.ClearScreen();
            running = renderer.ShowGameOverOptions();
            if (running) {
                snake = Snake(grid_width, grid_height, snake.speed);
                score = 0;
                PlaceFood();
            }
        }
        else {
            renderer.Dohoa(snake, food);
        }
        frame_end = SDL_GetTicks();
        frame_count++;
        frame_duration = frame_end - frame_start;
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}
void game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        if (!snake.SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}
void game::Update() {
    if (!snake.alive) return;

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);
    if (food.x == new_x && food.y == new_y) {
        score++;
        PlaceFood();
        snake.GrowBody();
    }
}
int game::GetScore() const { return score; }
int game::GetSize() const { return snake.size; }