
#include <raylib.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include "Cmath_extend.h"
#include "Game.h"

Cmath_extend math;




bool Is_init = false;


int main() {
	srand(static_cast<unsigned int>(time(nullptr)));
	
	

	InitWindow(960, 720, "Shooter game");
	game.Game_init();
	Is_init = true;

	SetTargetFPS(60);

	
	
	

	bool move = false;

	while (!WindowShouldClose()) {

		

		BeginDrawing();
		
		ClearBackground(BLACK);

		game.Game_update();

		EndDrawing();
	}
}