#pragma once
#include "Entity.h"
#include <raylib.h>
#include "Cmath_extend.h"

class Bullet : public Entity {
private:
	Vector2 vector_move;
	float attack;
public:
	Bullet(Vector2 pos, float w, float h, Color color, Vector2 vec_move, float attack) : Entity(pos, w, h, color), vector_move(vec_move), attack(attack) {

	}

	Bullet() : Entity(), vector_move({1, 1}), attack(1) {

	}

	~Bullet() {};
	void SetVectorMove(Vector2 vec) {
		this->vector_move = vector_move;
	}
	Vector2 GetVectorMove() {
		return this->vector_move;
	}
	void Init_bullet() {
		this->Move(this->vector_move.x, this->vector_move.y);
		DrawRectangle(this->GetStatus().Pos.x, this->GetStatus().Pos.y, this->GetStatus().w, this->GetStatus().h, this->GetStatus().color);
	}
	float GetAttack() {
		return this->attack;
	}
};