#include <iostream>
#include "dieukhien.h"
#include "game.h"
#include "dohoa.h"
//#include "resource.h"

int main() {
	constexpr std::size_t kFramesPerSecond{ 60 };
	constexpr std::size_t kMsPerFrame{ 1000 / kFramesPerSecond };
	constexpr std::size_t kScreenWidth{ 640 };
	constexpr std::size_t kScreenHeight{ 640 };
	constexpr std::size_t kGridWidth{ 32 };
	constexpr std::size_t kGridHeight{ 32 };

	dohoa renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
	dieukhien controller;
	if (renderer.ShowPlayButton()) {
		float speed = renderer.ShowSpeedOptions();
		game game(kGridWidth, kGridHeight, speed);
		game.Run(controller, renderer, kMsPerFrame);
		std::cout << "Game da hoan thanh!\n";
		std::cout << "DIEM: " << game.GetScore() << "\n";
		std::cout << "Kich thuoc: " << game.GetSize() << "\n";
	}
	return 0;
}


