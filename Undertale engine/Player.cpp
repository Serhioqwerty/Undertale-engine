#include <raylib.h>
#include "Engine/Player.h"

int Player::GetLvl() {
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
Player::Player(Vector2 vec, float Width, float Height, float health, int exp, Color color, Type_player type) : Entity(vec, Width, Height, color), health(health), exp(exp), vector_move({ 0, 0 }) {
	this->lvl = this->GetLvl();
	this->speed = 5;
	this->type_player = type;

}

void Player::GetEX(unsigned int exp) {
	this->exp = exp;
	this->lvl = this->GetLvl();
}


void Update_player();


void Player::Attack(float h) {
	this->health -= h;
}
void Player::SetHealth(float h) {
	this->health = h;
}
float Player::GetHealth() {
	return this->health;
}
Vector2 Player::GetOldPos() {
	return this->old_pos;
}