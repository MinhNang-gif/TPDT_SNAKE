#include "dohoa.h"
#include <iostream>
#include <string>

dohoa::dohoa(const std::size_t screen_width,
    const std::size_t screen_height,
    const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
    screen_height(screen_height),
    grid_width(grid_width),
    grid_height(grid_height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, screen_width,
        screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

dohoa::~dohoa() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}
void dohoa::ClearScreen() {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(sdl_renderer);
}

void dohoa::Dohoa(Snake const snake, SDL_Point const& food) {

    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0xFF);

    SDL_RenderClear(sdl_renderer);

    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 225, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    SDL_SetRenderDrawColor(sdl_renderer, 148, 255, 206, 0xFF);
    for (SDL_Point const& point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0, 79, 7, 0xFF);
    }
    else {
        SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    SDL_RenderPresent(sdl_renderer);

}

