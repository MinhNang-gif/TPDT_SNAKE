#include <iostream>
#include "dieukhien.h"
#include "game.h"
#include "dohoa.h"

int main() {
	constexpr std::size_t kFramesPerSecond{ 60 };
	constexpr std::size_t kMsPerFrame{ 1000 / kFramesPerSecond };
	constexpr std::size_t kScreenWidth{ 640 };
	constexpr std::size_t kScreenHeight{ 640 };
	constexpr std::size_t kGridWidth{ 8 };
	constexpr std::size_t kGridHeight{ 8 };

	dohoa renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);

	dieukhien controller;

	game game(kGridWidth, kGridHeight);

	if (!renderer.ShowPlayButton()) {
		return 0;
	}
	game.Run(controller, renderer, kMsPerFrame);
	std::cout << "Game has terminated successfully!\n";
	std::cout << "Score: " << game.GetScore() << "\n";
	std::cout << "Size: " << game.GetSize() << "\n";
	return 0;
}