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
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, screen_width,
        screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
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

void dohoa::Dohoa(Snake const snake, SDL_Point const& food) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render food
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const& point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    }
    else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    // Update Screen
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
    // Tạo nút "Play"
    SDL_Rect play_button;
    play_button.x = screen_width / 2 - 50; // Đặt vị trí của nút ở giữa màn hình
    play_button.y = screen_height / 2 - 25;
    play_button.w = 100; // Kích thước của nút
    play_button.h = 50;

    // Vẽ nút "Play"
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &play_button);
    SDL_Texture* play_image = LoadImage("th.png"); // Thay "path_to_your_image.png" bằng đường dẫn đến hình ảnh của bạn
    if (play_image) {
        SDL_RenderCopy(sdl_renderer, play_image, nullptr, &play_button);
        SDL_DestroyTexture(play_image); // Hủy texture sau khi đã sử dụng
    }

    // Cập nhật màn hình
    SDL_RenderPresent(sdl_renderer);

    // Kiểm tra sự kiện nhấp chuột
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
                // Nếu nhấp vào nút "Play", bắt đầu trò chơi
                return true;
            }
        }
    }

    return false;
    }
void dohoa::UpdateWindowTitle(int score, int fps) {
    std::string title{ "Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) };
    SDL_SetWindowTitle(sdl_window, title.c_str());
}