#include <raylib.h>
#include "Engine/Game.h"
#include <vector>
#include "Engine/Audio.h"

extern Audio_class audio_c;

bool Game::RayCasting(Vector2& enemy, float distance) {
	float k = 1;
	Rectangle rect = { enemy.x, enemy.y, 5, 5 };
	Rectangle rect_wall;
	Vector2 player_pos = this->player->GetPos();
	Vector2 vector_move = math.GetVectorMove(player_pos, enemy);

	Vector2 Pos_player = player->GetPos();
	Vector2 rect_pos = { rect.x, rect.y };
	while (math.GetDistance(Pos_player, rect_pos) < distance) {
		rect.x += vector_move.x * k;
		rect.y += vector_move.y * k;
		for (auto& w : Walls) {
			rect_wall = w->GetRec();
			DrawRectangle(rect.x, rect.y, rect.width, rect.height, { 0, 121, 241, 25 });

			if (CheckCollisionRecs(rect, rect_wall)) {

				return false;
			}
			if (CheckCollisionRecs(rect, player->GetRec())) {

				return true;
			}
		}
	}
	return false;


}

void Game::UI_update() {
	for (int i = 0; i < Elements.size(); i++) {
		Elements[i]->Render();
		if (i == this->index_health_ui) {
			health_text = std::to_string(player->GetHealth());
			Elements[i]->SetText(health_text.c_str());
		}
	}
}

void Game::Bullet_update() {
	for (auto& b : Bullets) {
		b->Render();
		b->Move(b->GetVectorMove().x, b->GetVectorMove().y);
	}

}

void Game::Collision_update() {
	for (int i = 0; i < Game::Bullets.size(); i++) {
		if (CheckCollisionRecs({ player->GetStatus().Pos.x, player->GetPos().y, player->GetStatus().w, player->GetStatus().h }, { Bullets[i]->GetStatus().Pos.x, Bullets[i]->GetStatus().Pos.y, Bullets[i]->GetStatus().w, Bullets[i]->GetStatus().h })) {
			player->Attack(Bullets[i]->GetAttack());
			Bullets.erase(Bullets.begin() + i);

		}
		//если пули попадают в стену
		for (auto& w : Walls) {
			if (CheckCollisionRecs(Bullets[i]->GetRec(), w->GetRec())) {
				Bullets.erase(Bullets.begin() + i);
			}
		}
	}

}

//обновление твердых коллизий
void Game::Col_update(Rectangle& hitbox_object) {
	//провка левой стены
	if (this->player->GetPos().x > hitbox_object.x - this->player->GetStatus().w * 1.125 and this->player->GetPos().x < hitbox_object.x + 0.5) {
		if (this->player->GetPos().y > hitbox_object.y - this->player->GetStatus().h and this->player->GetPos().y < hitbox_object.y + (hitbox_object.height)) {
			this->player->SetPos({ hitbox_object.x - this->player->GetStatus().w * 1.125f, this->player->GetPos().y });
		}
	}
	//проверка правой стены
	if (this->player->GetPos().x < hitbox_object.x + hitbox_object.width + this->player->GetStatus().w - 4 and this->player->GetPos().x > hitbox_object.x + hitbox_object.width - 0.5) {
		if (this->player->GetPos().y > hitbox_object.y - this->player->GetStatus().h and this->player->GetPos().y < hitbox_object.y + (hitbox_object.height)) {
			this->player->SetPos({ hitbox_object.x + hitbox_object.width + this->player->GetStatus().w - 4, this->player->GetPos().y });
		}
	}
	//проверка верхней стены
	if (this->player->GetPos().y > hitbox_object.y - this->player->GetStatus().h * 1.125 and this->player->GetPos().y < hitbox_object.y + 0.5) {
		if (this->player->GetPos().x > hitbox_object.x - this->player->GetStatus().w and this->player->GetPos().x < hitbox_object.x + hitbox_object.width) {
			this->player->SetPos({ this->player->GetPos().x, hitbox_object.y - this->player->GetStatus().h * 1.125f });
		}
	}
	//проверка нижней стены
	if (this->player->GetPos().y < hitbox_object.y + hitbox_object.height + this->player->GetStatus().w - 4 and this->player->GetPos().y > hitbox_object.y + hitbox_object.height - 0.5) {
		if (this->player->GetPos().x > hitbox_object.x - this->player->GetStatus().w and this->player->GetPos().x < hitbox_object.x + hitbox_object.width) {
			this->player->SetPos({ this->player->GetPos().x, hitbox_object.y + hitbox_object.height + this->player->GetStatus().h - 4 });
		}
	}
}

void Game::Wall_update() {
	for (int i = 0; i < Walls.size(); i++) {
		Rectangle r = Walls[i]->GetRec();
		Col_update(r);
		Walls[i]->Render();

	}
}

void Game::Enemy_update() {
	for (auto& e : Enemys) {
		e->Render();
		Vector2 pos = { e->GetPos().x + e->GetStatus().w / 2, e->GetPos().y + e->GetStatus().h / 2 };
		bool is_view = RayCasting(pos, 500);
		if (is_view) {
			e->Shoot();
		}
	}

}

void Game::CreateEnemy(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta, Type_attack t, const char* texture) {
	Enemys.push_back(std::make_unique<Enemy>(pos, W, H, c, Health, Attack, ta, t, texture));
}

Enemy* Game::CreateEnemyWithPointer(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta, Type_attack t, const char* texture) {
	Enemys.push_back(std::make_unique<Enemy>(pos, W, H, c, Health, Attack, ta, t, texture));
	int last = Enemys.size() - 1;
	return Enemys[last].get();
}
int Game::CreateEnemyWithIndex(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta, Type_attack t, const char* texture) {
	Enemys.push_back(std::make_unique<Enemy>(pos, W, H, c, Health, Attack, ta, t, texture));
	return Enemys.size() - 1;
}


Wall* Game::GetWallPointer(int index) {
	return this->Walls[index].get();
}

Wall* Game::GetLastWallPointer() {
	return this->GetWallPointer(Walls.size() - 1);
}

Wall* Game::CreateWallWithPointer(Vector2 pos, float W, float H, Color c) {
	Walls.push_back(std::make_unique<Wall>(pos, W, H, c));
	int last = Walls.size() - 1;
	return Walls[last].get();
}
int Game::CreateWallWithIndex(Vector2 pos, float W, float H, Color c) {
	Walls.push_back(std::make_unique<Wall>(pos, W, H, c));
	return Walls.size() - 1;
}

void Game::CreateWall(Vector2 pos, float W, float H, Color c) {
	Walls.push_back(std::make_unique<Wall>(pos, W, H, c));
}

void Game::CreateUI(Vector2 pos_box, Vector2 pos_text, float W, float H, Color c, const char* t) {
	Elements.push_back(std::make_unique<Element>(pos_box, pos_text, W, H, c, t));
}

void Game::SetPlayer(Vector2 pos, float W, float H, Color c, float health, int exp, Type_player type) {
	player = std::make_unique<Player>(pos, W, H, health, exp, c, type);
}



void Player::Update_player() {
	this->old_pos = this->GetPos();
	this->Move(this->vector_move.x, this->vector_move.y);
	this->Render();
	if (this->type_player == Type_player::DEFAULT) {
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
	else if (this->type_player == Type_player::PHYSIC) {



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
		if (IsKeyDown(KEY_UP)) {
			if (this->is_gravity == false) {
				this->is_gravity = true;
				this->vector_move.y = -5;
			}
		}

		float frame_sec = GetFrameTime();
		if (is_gravity == true) {
			this->vector_move.y += frame_sec * this->gravity;
		}

		for (auto& w : game.Walls) {
			if (CheckCollisionRecs(this->GetRec(), w->GetRec())) {
				this->is_gravity = false;
			}
			else {
				this->is_gravity = true;
			}
		}
		if (this->is_gravity == false) {
			this->vector_move.y = 0;
		}
	}
}

void Game::DeleteWallWithIndex(int index) {
	Walls.erase(Walls.begin() + index);
}

void Game::DeleteWallWithPointer(Wall* ptr) {
	for (int i = 0; i < Walls.size(); i++) {
		if (Walls[i].get() == ptr) {
			Walls.erase(Walls.begin() + i);
		}
	}
}

void Game::DeleteAllWalls() {
	Walls.clear();
}


void Game::DeleteWallWithSmartPointer(std::unique_ptr<Wall>& smart_ptr) {
	smart_ptr.reset();
}

void Game::DeleteEnemyWithIndex(int index) {
	Enemys.erase(Enemys.begin() + index);
}

void Game::DeleteEnemyWithPointer(Enemy* ptr) {
	for (int i = 0; i < Enemys.size(); i++) {
		if (Enemys[i].get() == ptr) {
			Enemys.erase(Enemys.begin() + i);
		}
	}
}

void Game::DeleteAllEnemys() {
	Enemys.clear();
}

void DeleteEnemyWithSmartPointer(std::unique_ptr<Enemy>& smart_ptr) {
	smart_ptr.reset();
}

void Game::Game_update() {
	ClearBackground(BLACK);
	player->Update_player();
	Collision_update();
	Bullet_update();
	Wall_update();
	Enemy_update();
	audio_c.Update_music();
	Custom_update();
	UI_update();
}