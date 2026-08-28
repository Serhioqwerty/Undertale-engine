#include <raylib.h>
#include <vector>
#include "Player.h"
#include "Entity.h"
#include "Bullet.h"
#include "UI.h"
#include <memory>
#include <string>
#include "Wall.h"
#include "Game.h"

struct Clock {
	float timer = 0;
	float dt = GetFrameTime();
	void UpdateTime() {
		timer += dt;
	}
};

Clock time;

void Game::Custom_update(void) {
	time.UpdateTime();
}