#pragma once
#include <raylib.h>
#include <vector>
#include "Player.h"
#include "Entity.h"
#include "Bullet.h"
#include "UI.h"
#include <memory>
#include <string>

class Game {
private:
	float RAM;
	int index_health_ui;
	std::string health_text;
public:
	std::vector<std::unique_ptr<Bullet>>Bullets;
	std::unique_ptr<Player>player;
	std::vector<std::unique_ptr<Enemy>>Enemys;
	std::vector<std::unique_ptr<Element>>Elements;

	Game() : RAM(0) {
		
	}
	void SetPlayer(Vector2 pos, float W, float H, Color c, float health, int exp) {
		player = std::make_unique<Player>(pos, W, H, health, exp, c);
	}
	void UpdateRam() {
		int bytes_Bullets = sizeof(Bullet) * Bullets.size();
		this->RAM = bytes_Bullets;
	}
	void CreateUI(Vector2 pos_box, Vector2 pos_text, float W, float H, Color c, const char* t) {
		Elements.push_back(std::make_unique<Element>(pos_box, pos_text, W, H, c, t));
	}

	void Collision_update() {
		for (int i = 0; i < Bullets.size(); i++) {
			if (CheckCollisionRecs({ player->GetStatus().Pos.x, player->GetPos().y, player->GetStatus().w, player->GetStatus().h }, { Bullets[i]->GetStatus().Pos.x, Bullets[i]->GetStatus().Pos.y, Bullets[i]->GetStatus().w, Bullets[i]->GetStatus().h })) {
				player->Attack(Bullets[i]->GetAttack());
				Bullets.erase(Bullets.begin() + i);
				player->Attack(Bullets[i]->GetAttack());
				i--;
			}
		}
	}

	void CreateEnemy(Vector2 pos, float W, float H, Color c, float Health, float Attack, float t) {
		Enemys.push_back(std::make_unique<Enemy>(pos, W, H, c, Health, Attack, t));
	}
	
	void Enemy_update() {
		for (auto& e : Enemys) {
			DrawRectangle(e->GetPos().x, e->GetPos().y, e->GetStatus().w, e->GetStatus().h, e->GetStatus().color);
			e->Triple_shoot();
		}

	}

	void Bullet_update() {
		for (auto& b : Bullets) {
			DrawRectangle(b->GetStatus().Pos.x, b->GetStatus().Pos.y, b->GetStatus().w, b->GetStatus().h, b->GetStatus().color);
			b->Move(b->GetVectorMove().x, b->GetVectorMove().y);
		}
		
	}
	void UI_update() {
		for (int i = 0; i < Elements.size(); i++) {
			Elements[i]->Render();
			if (i == this->index_health_ui) {
				health_text = std::to_string(player->GetHealth());
				Elements[i]->SetText(health_text.c_str());
			}
		}
	}

	void Custom_update() {

	}

	void Game_init() {
		SetPlayer({ 200, 200 }, 10, 10, YELLOW, 92, 100);
		CreateUI({ 0, 680 }, { 10, 20 }, 960, 40, GRAY, "0");
		this->index_health_ui = Elements.size() - 1;
		CreateEnemy({ 400, 30 }, 50, 50, RED, 100, 1, 0.5);
		CreateEnemy({ 100, 300 }, 50, 50, RED, 100, 1, 0.5);
		CreateEnemy({ 700, 200 }, 50, 50, RED, 100, 1, 0.5);
	}


	void Game_update() {
		player->Update_player();
		Collision_update();
		Bullet_update();
		Enemy_update();
		Custom_update();
		UI_update();
	}

};

extern Game game;