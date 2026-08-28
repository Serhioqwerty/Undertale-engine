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

const float intervale_with_one_operation = 0.012;

class Clock {
private:
	float timer;
public:
	Clock() {
		this->timer = 0;
	}
	float GetTimer() {
		return this->timer;
	}
	void Update() {
		float dt = GetFrameTime();
		timer += dt;
	}
};



Clock time_engine;


void Game::Custom_update() {
	time_engine.Update();
	if (math.Intervale_if(time_engine.GetTimer(), 2.0f, intervale_with_one_operation)) {
		std::cout << "jopa";
		game.CreateEnemy({ 50, 700 }, 100, 100, RED, 120, 1, 0.5);
	}
	if (math.Intervale_if(time_engine.GetTimer(), 5.0f, 2.2)) {
		int last = game.Enemys.size() - 1;
		game.Enemys[last]->Move(0, -1);
	}
	if (math.Intervale_if(time_engine.GetTimer(), 15.2, 10)) {
		int last = game.Enemys.size() - 1;
		game.Enemys[last]->Move(1, 0);
	}
}