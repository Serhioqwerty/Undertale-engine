
#include <raylib.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include "Engine/Cmath_extend.h"
#include "Engine/Game.h"

Cmath_extend math;




bool Is_init = false;


int main() {
	game.Game_init();
	Is_init = true;

	while (!WindowShouldClose()) {

		BeginDrawing();
		
		game.Game_update();

		EndDrawing();
	}
}