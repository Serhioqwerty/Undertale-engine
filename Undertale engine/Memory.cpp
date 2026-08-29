#include <raylib.h>
#include <vector>
#include "Engine/Game.h"

void Game::UpdateRam() {
	int bytes_Bullets = sizeof(Bullet) * Bullets.size();
	this->RAM = bytes_Bullets;
}