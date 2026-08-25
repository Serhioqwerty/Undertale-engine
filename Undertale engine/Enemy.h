#pragma once

#include "Entity.h"

#include <raylib.h>
#include "Cmath_extend.h"


class Game;
extern Game game;
extern Cmath_extend math;

enum class Type_attack {DEFAULT, TRIPLE};

class Enemy : public Entity {
private:
	float Health;
	float Attack;
	float timer;
	float target;
public:
	~Enemy() {
		
	}

	Enemy(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta) : Entity(pos, W, H, c), Health(Health), Attack(Attack), timer(0), target(ta) {
		if (Health <= 0) {
			return;
		}
		
	}

	void Shoot(Type_attack type);

	Enemy() : Entity(), Health(1), Attack(1), timer(0), target(5) {
		if (Health <= 0) {
			return;
		}

	}

	void default_shoot() {
		float frame = GetFrameTime();
		this->timer += frame;
		if (this->timer >= target) {
			Shoot(Type_attack::DEFAULT);
			this->timer = 0;
		}
	}

	void Triple_shoot() {
		float frame = GetFrameTime();
		this->timer += frame;
		if (this->timer >= target) {
			Shoot(Type_attack::TRIPLE);
			this->timer = 0;
		}
	}

};
