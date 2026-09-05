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
#include "Engine/Audio.h"

const float intervale_with_one_operation = 0.012;

Audio_class audio_c;

/*
Таймер для задержки между событиями. Раюотает в одном потоке. Заменяет Sleep (он блокирует поток).
Лля проверки времени лучше использовать math.Intervale_if
*/

class Clock {
private:
	float timer;
	int int_timer;
public:
	Clock() {
		this->timer = 0;
	}
	float GetTimer() {
		return this->timer;
	}

	int GetTimerInt() {
		return this->int_timer;
	}

	void Update() {
		float dt = GetFrameTime();
		timer += dt;
		int_timer = timer;
	}
};



Clock time_engine;

int test;

bool operation = false;

//точка входа в user-main (нужно использовать обычный С++ код, чтобы писать события).
void Game::Custom_update() {
	time_engine.Update();
	if (time_engine.GetTimer() > 2 and time_engine.GetTimerInt() % 4 == 0) {
		std::cout << "Time: " << time_engine.GetTimerInt() << std::endl;
		this->Walls[test]->Move(0, 1);
	}
	if (time_engine.GetTimerInt() == 2 and operation == false) {
		test = CreateWallWithIndex({player->GetPos().x + 100, player->GetPos().y - 100}, 100, 100, ORANGE);
		operation = true;
	}
	
	
}