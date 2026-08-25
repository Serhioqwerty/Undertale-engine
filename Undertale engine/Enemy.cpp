#include <raylib.h>
#include "Cmath_extend.h"
#include "Game.h"
#include "Enemy.h"

Game game;

void Enemy::Shoot(Type_attack type) {
	if (type == Type_attack::DEFAULT) {
		float timer = 0;
		float frame = GetFrameTime();
		float deltaTarget = 2;
		float pos_x_player = game.player->GetPos().x;
		float pos_y_player = game.player->GetPos().y;
		float pos_x_this = this->GetPos().x + this->GetStatus().w / 2;
		float pos_y_this = this->GetPos().y + this->GetStatus().h / 2;
		Vector2 vec_move = math.GetVectorMove({ pos_x_player, pos_y_player } , { pos_x_this, pos_y_this } );
		Vector2 vec_this = { pos_x_this, pos_y_this };
		while (timer < deltaTarget) {
			timer += frame;
		}
		game.Bullets.push_back(std::make_unique<Bullet>(vec_this, 5, 5, WHITE, vec_move, 1));
	}
	else if (type == Type_attack::TRIPLE) {
		Vector2 PosPlayer = game.player->GetPos();
		Vector2 PosThis = this->GetPos();
		Vector2 vec_move_center = math.GetVectorMove(PosPlayer, PosThis);
		Vector2 rotation_right = math.GetRotation(20);
		Vector2 rotation_left = math.GetRotation(0);
		Vector2 vec_right = math.MultiplyVector(rotation_right, vec_move_center);
		Vector2 vec_left = math.MultiplyVector(rotation_left, vec_move_center);
		game.Bullets.push_back(std::make_unique<Bullet>(PosThis, 5, 5, WHITE, vec_move_center, 1));
		game.Bullets.push_back(std::make_unique<Bullet>(PosThis, 5, 5, WHITE, vec_right, 1));
		game.Bullets.push_back(std::make_unique<Bullet>(PosThis, 5, 5, WHITE, vec_left, 1));
	}
	
}