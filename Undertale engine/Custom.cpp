#include <raylib.h>
#include <vector>
#include "Engine/Player.h"
#include "Engine/Entity.h"
#include "Engine/Bullet.h"
#include "Engine/UI.h"
#include <memory>
#include <string>
#include "Engine/Wall.h"
#include "Engine/Game.h"

const float intervale_with_one_operation = 0.012;

/*
Таймер для задержки между событиями. Раюотает в одном потоке. Заменяет Sleep (он блокирует поток).
Лля проверки времени лучше использовать math.Intervale_if
*/

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

//точка входа в user-main (нужно использовать обычный С++ код, чтобы писать события).
void Game::Custom_update() {
	time_engine.Update();
	if (math.Intervale_if(time_engine.GetTimer(), 2.0f, intervale_with_one_operation)) {
		std::cout << "jopa";
		game.CreateEnemy({ 50, 700 }, 100, 100, RED, 120, 1, 0.5, Type_attack::TRIPLE);
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