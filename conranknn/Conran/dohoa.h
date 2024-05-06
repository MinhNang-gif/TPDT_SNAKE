#pragma once
#ifndef RENDERER_H
#define RENDERER_H
#include<string>
#include <vector>
#include "SDL.h"
#include "snake.h"
#include "SDL_image.h"
class dohoa {
public:
    dohoa(const std::size_t screen_width, const std::size_t screen_height,
        const std::size_t grid_width, const std::size_t grid_height);
    ~dohoa();

    void Dohoa(Snake const snake, SDL_Point const& food);
    void UpdateWindowTitle(int score, int fps);
    SDL_Texture* LoadImage(const std::string& file);
    bool ShowPlayButton();

private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif

