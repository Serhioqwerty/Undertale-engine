#include <raylib.h>
#include "Engine/Cmath_extend.h"
#include "Engine/Game.h"
#include "Engine/Enemy.h"


Game game;

void Enemy::Shoot() {
	float dt = GetFrameTime();
	this->timer += dt;
	if (timer >= this->target) {
		if (this->type == Type_attack::DEFAULT) {
			float deltaTarget = 2;
			float pos_x_player = game.player->GetPos().x + game.player->GetStatus().w / 2;
			float pos_y_player = game.player->GetPos().y + game.player->GetStatus().h / 2;
			float pos_x_this = this->GetPos().x + this->GetStatus().w / 2;
			float pos_y_this = this->GetPos().y + this->GetStatus().h / 2;
			Vector2 vec_move = math.GetVectorMove({ pos_x_player, pos_y_player }, { pos_x_this, pos_y_this });
			Vector2 vec_this = { pos_x_this, pos_y_this };
			game.Bullets.push_back(std::make_unique<Bullet>(vec_this, 5, 5, WHITE, vec_move, 1));
		}
		else if (this->type == Type_attack::TRIPLE) {
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

		this->timer = 0;
	}
	
}