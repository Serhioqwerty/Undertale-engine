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
	Type_attack type;
public:
	~Enemy() {
		
	}

	Enemy(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta, Type_attack t) : Entity(pos, W, H, c, 0), Health(Health), Attack(Attack), timer(0), target(ta) {
		if (Health <= 0) {
			return;
		}
		this->type = t;

	}

	Enemy(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta, Type_attack t, const char* texture) : Entity(pos, W, H, c, texture), Health(Health), Attack(Attack), timer(0), target(ta) {
		if (Health <= 0) {
			return;
		}
		this->type = t;

	}

	void Shoot();

	Enemy() : Entity(), Health(1), Attack(1), timer(0), target(5) {
		if (Health <= 0) {
			return;
		}

	}

	Type_attack Get_type() {
		return this->type;
	}
};
