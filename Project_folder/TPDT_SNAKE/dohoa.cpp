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

    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.w = screen_width;
    background_rect.h = screen_height;

    SDL_Texture* background_image = LoadImage("sanchoi5.png");

    if (background_image) {
        SDL_RenderCopy(sdl_renderer, background_image, NULL, &background_rect);
        SDL_DestroyTexture(background_image);
    }

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

SDL_Texture* dohoa::LoadImage(const std::string& file) {
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << file << "\n";
        std::cerr << "IMG Error: " << IMG_GetError() << "\n";
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface.\n";
        std::cerr << "SDL Error: " << SDL_GetError() << "\n";
    }

    SDL_FreeSurface(surface);
    return texture;
}

bool dohoa::ShowPlayButton() {
    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.w = screen_width;
    background_rect.h = screen_height;

    SDL_Texture* background_image = LoadImage("nengame.png");

    if (background_image) {
        SDL_RenderCopy(sdl_renderer, background_image, NULL, &background_rect);
        SDL_DestroyTexture(background_image);
    }

    SDL_Rect play_button;
    play_button.x = screen_width / 2 - 43;
    play_button.y = screen_height / 2 + 33;
    play_button.w = 95;
    play_button.h = 95;
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &play_button);
    SDL_Texture* play_image = LoadImage("play22.png");
    if (play_image) {
        SDL_RenderCopy(sdl_renderer, play_image, nullptr, &play_button);
        SDL_DestroyTexture(play_image);
    }

    SDL_RenderPresent(sdl_renderer);

    SDL_Event e;
    while (SDL_WaitEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= play_button.x && x <= play_button.x + play_button.w &&
                y >= play_button.y && y <= play_button.y + play_button.h) {
                return true;
            }
        }
    }

    return false;
}
float dohoa::ShowSpeedOptions() {

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(sdl_renderer);

    SDL_Texture* background_image = LoadImage("menu.png");
    SDL_Rect background_rect{ 0, 0, screen_width, screen_height };
    SDL_RenderCopy(sdl_renderer, background_image, NULL, &background_rect);

    SDL_Rect speed_option1{ screen_width / 2 + 122, screen_height / 2 - 107, 101, 101 };
    SDL_Rect speed_option2{ screen_width / 2 - 49, screen_height / 2 - 107, 101, 101 };
    SDL_Rect speed_option3{ screen_width / 2 - 221, screen_height / 2 - 107, 101, 101 };

    SDL_Texture* hard_image = LoadImage("hard2.png");
    SDL_Texture* medium_image = LoadImage("medium2.png");
    SDL_Texture* easy_image = LoadImage("eze2.png");

    SDL_RenderCopy(sdl_renderer, hard_image, NULL, &speed_option1);
    SDL_RenderCopy(sdl_renderer, medium_image, NULL, &speed_option2);
    SDL_RenderCopy(sdl_renderer, easy_image, NULL, &speed_option3);

    SDL_DestroyTexture(hard_image);
    SDL_DestroyTexture(medium_image);
    SDL_DestroyTexture(easy_image);

    SDL_RenderPresent(sdl_renderer);

    SDL_Event e;
    while (SDL_WaitEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return 0.0f;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= speed_option1.x && x <= speed_option1.x + speed_option1.w &&
                y >= speed_option1.y && y <= speed_option1.y + speed_option1.h) {
                return 0.4f;
            }
            else if (x >= speed_option2.x && x <= speed_option2.x + speed_option2.w &&
                y >= speed_option2.y && y <= speed_option2.y + speed_option2.h) {
                return 0.2f;
            }
            else if (x >= speed_option3.x && x <= speed_option3.x + speed_option3.w &&
                y >= speed_option3.y && y <= speed_option3.y + speed_option3.h) {
                return 0.1f;
            }
        }
    }

    return 0.0f;
}
bool dohoa::ShowGameOverOptions() {
    SDL_Rect play_again_button{ screen_width / 2 - 115, screen_height * 3 / 4 - 200, 100, 100 };
    SDL_Rect quit_button{ screen_width / 2 + 15, screen_height * 3 / 4 - 200, 100, 100 };

    SDL_Texture* play_again_image = LoadImage("playover.png");
    SDL_Texture* quit_image = LoadImage("quit2.png");

    SDL_RenderCopy(sdl_renderer, play_again_image, NULL, &play_again_button);
    SDL_RenderCopy(sdl_renderer, quit_image, NULL, &quit_button);

    SDL_DestroyTexture(play_again_image);
    SDL_DestroyTexture(quit_image);

    SDL_RenderPresent(sdl_renderer);

    SDL_Event e;
    while (SDL_WaitEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (x >= play_again_button.x && x <= play_again_button.x + play_again_button.w &&
                y >= play_again_button.y && y <= play_again_button.y + play_again_button.h) {
                return true;
            }
            else if (x >= quit_button.x && x <= quit_button.x + quit_button.w &&
                y >= quit_button.y && y <= quit_button.y + quit_button.h) {
                return false;
            }
        }
    }
    return false;
}
void dohoa::GameOverScreen() {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(sdl_renderer);
    SDL_Rect game_over_rect;
    game_over_rect.x = screen_width / 2 - 100;
    game_over_rect.y = screen_height / 2 - 50;
    game_over_rect.w = 200;
    game_over_rect.h = 100;

    SDL_Surface* button_surface = IMG_Load("gameo.png");
    if (!button_surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << "\n";
        return;
    }
    SDL_Texture* button_texture = SDL_CreateTextureFromSurface(sdl_renderer, button_surface);

    SDL_RenderCopy(sdl_renderer, button_texture, NULL, &game_over_rect);

    SDL_FreeSurface(button_surface);
    SDL_DestroyTexture(button_texture);

    SDL_RenderPresent(sdl_renderer);
}
void dohoa::UpdateWindowTitle(int score, int fps) {
    std::string title{ "Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) };
    SDL_SetWindowTitle(sdl_window, title.c_str());
}