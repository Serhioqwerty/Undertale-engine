#pragma once
#include "Entity.h"
#include "Enemy.h"




class Player : public Entity {
private:

	float health;
	int lvl;
	int exp;
	float speed;
	Vector2 vector_move;
	Vector2 old_pos;
public:
	int GetLvl() {
		if (this->exp >= 30000) {
			return 20;
		}
		else if (this->exp >= 20000) {
			return 19;
		}
		else if (this->exp >= 15000) {
			return 18;
		}
		else if (this->exp >= 12000) {
			return 17;
		}
		else if (this->exp >= 10000) {
			return  16;
		}
		else if (this->exp >= 9000) {
			return 15;
		}
		else if (this->exp >= 7500) {
			return 14;
		}
		else if (this->exp >= 5000) {
			return  13;
		}
		else if (this->exp >= 3000) {
			return 12;
		}
		else if (this->exp >= 2500) {
			return 11;
		}
		else if (this->exp >= 1500) {
			return 10;
		}
		else if (this->exp >= 1000) {
			return 9;
		}
		else if (this->exp >= 800) {
			return 8;
		}
		else if (this->exp >= 600) {
			return 7;
		}
		else if (this->exp >= 500) {
			return 6;
		}
		else if (this->exp >= 400) {
			return 5;
		}
		else if (this->exp >= 350) {
			return 4;
		}
		else if (this->exp >= 300) {
			return 3;
		}
		else if (this->exp >= 100) {
			return 2;
		}
		else if (this->exp >= 0) {
			return 1;
		}
		else {
			return 1;
		}
	}
	Player(Vector2 vec, float Width, float Height, float health, int exp, Color color) : Entity(vec, Width, Height, color), health(health), exp(exp), vector_move({ 0, 0 }) {
		this->lvl = this->GetLvl();
		this->speed = 5;
	}
	
	void GetEX(unsigned int exp) {
		this->exp = exp;
		this->lvl = this->GetLvl();
	}
	

	void Update_player() {
		this->old_pos = this->GetPos();
		this->Move(this->vector_move.x, this->vector_move.y);
		this->Render();
		if (IsKeyDown(KEY_UP)) {
			this->vector_move.y = -speed;
		}
		else if (IsKeyDown(KEY_DOWN)) {
			this->vector_move.y = speed;
		}
		else {
			this->vector_move.y = 0;
		}
		if (IsKeyDown(KEY_LEFT)) {
			this->vector_move.x = -speed;
		}
		else if (IsKeyDown(KEY_RIGHT)) {
			this->vector_move.x = speed;
		}
		else {
			this->vector_move.x = 0;
		}
		if (IsKeyDown(KEY_X)) {
			this->speed = 1.5;
		}
		else {
			this->speed = 5;
		}
		
		
	}
	void Attack(float h) {
		this->health -= h;
	}
	void SetHealth(float h) {
		this->health = h;
	}
	float GetHealth() {
		return this->health;
	}
	Vector2 GetOldPos() {
		return this->old_pos; 
	}
};
