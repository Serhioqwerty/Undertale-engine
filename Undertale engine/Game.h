#pragma once
#include <raylib.h>
#include <vector>
#include "Player.h"
#include "Entity.h"
#include "Bullet.h"
#include "UI.h"
#include <memory>
#include <string>
#include "Wall.h"

class Game {
private:
	float RAM; //память со всех массивов
	int index_health_ui; //Индекс на UI обьект
	std::string health_text; //Текст здоровья
public:
	//массивы
	std::vector<std::unique_ptr<Bullet>>Bullets;
	std::unique_ptr<Player>player;
	std::vector<std::unique_ptr<Enemy>>Enemys;
	std::vector<std::unique_ptr<Element>>Elements;
	std::vector<std::unique_ptr<Wall>>Walls;

	Game() : RAM(0) {
		
	}

	//функция иницилизации игрока
	void SetPlayer(Vector2 pos, float W, float H, Color c, float health, int exp) {
		player = std::make_unique<Player>(pos, W, H, health, exp, c);
	}

	//обновление памяти (заброшено)
	void UpdateRam() {
		int bytes_Bullets = sizeof(Bullet) * Bullets.size();
		this->RAM = bytes_Bullets;
	}
	//создание UI
	void CreateUI(Vector2 pos_box, Vector2 pos_text, float W, float H, Color c, const char* t) {
		Elements.push_back(std::make_unique<Element>(pos_box, pos_text, W, H, c, t));
	}
	//обновление твердых коллизий
	void Col_update(Rectangle& hitbox_object) {
		//провка левой стены
		if (this->player->GetPos().x > hitbox_object.x - this->player->GetStatus().w * 1.125 and this->player->GetPos().x < hitbox_object.x + 0.5) {
			if (this->player->GetPos().y > hitbox_object.y - this->player->GetStatus().h and this->player->GetPos().y < hitbox_object.y + (hitbox_object.height)) {
				this->player->SetPos({ hitbox_object.x - this->player->GetStatus().w * 1.125f, this->player->GetPos().y });
			}
		}
		//проверка правой стены
		if (this->player->GetPos().x < hitbox_object.x + hitbox_object.width + this->player->GetStatus().w - 4 and this->player->GetPos().x > hitbox_object.x + hitbox_object.width - 0.5) {
			if (this->player->GetPos().y > hitbox_object.y - this->player->GetStatus().h and this->player->GetPos().y < hitbox_object.y + (hitbox_object.height)) {
				this->player->SetPos({ hitbox_object.x + hitbox_object.width + this->player->GetStatus().w - 4, this->player->GetPos().y});
			}
		}
		//проверка верхней стены
		if (this->player->GetPos().y > hitbox_object.y - this->player->GetStatus().h * 1.125 and this->player->GetPos().y < hitbox_object.y + 0.5) {
			if (this->player->GetPos().x > hitbox_object.x - this->player->GetStatus().w and this->player->GetPos().x < hitbox_object.x + hitbox_object.width) {
				this->player->SetPos({ this->player->GetPos().x, hitbox_object.y - this->player->GetStatus().h * 1.125f});
			}
		}
		//проверка нижней стены
		if (this->player->GetPos().y < hitbox_object.y + hitbox_object.height + this->player->GetStatus().w - 4 and this->player->GetPos().y > hitbox_object.y + hitbox_object.height - 0.5) {
			if (this->player->GetPos().x > hitbox_object.x - this->player->GetStatus().w and this->player->GetPos().x < hitbox_object.x + hitbox_object.width) {
				this->player->SetPos({ this->player->GetPos().x, hitbox_object.y + hitbox_object.height + this->player->GetStatus().h - 4});
			}
		}
	}

	//создание обьекта с твердыми колизиями
	void CreateWall(Vector2 pos, float W, float H, Color c) {
		Walls.push_back(std::make_unique<Wall>(pos, W, H, c));
	}

	//обновление колизий у пуль
	void Collision_update() {
		for (int i = 0; i < Bullets.size(); i++) {
			if (CheckCollisionRecs({ player->GetStatus().Pos.x, player->GetPos().y, player->GetStatus().w, player->GetStatus().h }, { Bullets[i]->GetStatus().Pos.x, Bullets[i]->GetStatus().Pos.y, Bullets[i]->GetStatus().w, Bullets[i]->GetStatus().h })) {
				player->Attack(Bullets[i]->GetAttack());
				Bullets.erase(Bullets.begin() + i);
				i--;
			}
			//если пули попадают в стену
			for (auto& w : Walls) {
				if (CheckCollisionRecs(Bullets[i]->GetRec(), w->GetRec())) {
					Bullets.erase(Bullets.begin() + i);
					i--;
				}
			}
		}
		
	}
	//создание врага
	void CreateEnemy(Vector2 pos, float W, float H, Color c, float Health, float Attack, float t) {
		Enemys.push_back(std::make_unique<Enemy>(pos, W, H, c, Health, Attack, t));
	}
	
	//Обновление врагов
	void Enemy_update() {
		for (auto& e : Enemys) {
			DrawRectangle(e->GetPos().x, e->GetPos().y, e->GetStatus().w, e->GetStatus().h, e->GetStatus().color);
			e->Triple_shoot();
		}

	}
	//Обновление пуль
	void Bullet_update() {
		for (auto& b : Bullets) {
			DrawRectangle(b->GetStatus().Pos.x, b->GetStatus().Pos.y, b->GetStatus().w, b->GetStatus().h, b->GetStatus().color);
			b->Move(b->GetVectorMove().x, b->GetVectorMove().y);
		}
		
	}

	//Обновление UI
	void UI_update() {
		for (int i = 0; i < Elements.size(); i++) {
			Elements[i]->Render();
			if (i == this->index_health_ui) {
				health_text = std::to_string(player->GetHealth());
				Elements[i]->SetText(health_text.c_str());
			}
		}
	}

	//Обновление стены, включающая обновление твердых коллизий
	void Wall_update() {
		for (int i = 0; i < Walls.size(); i++) {
			Rectangle r = Walls[i]->GetRec();
			Col_update(r);
			DrawRectangle(Walls[i]->GetPos().x, Walls[i]->GetPos().y, Walls[i]->GetRec().width, Walls[i]->GetRec().height, Walls[i]->GetStatus().color);
		}
	}


	//Пользовательское обновление, где программист сможет добавляиь свое
	void Custom_update() {

	}

	//Иницилизация игры. Нужна для певроначального создания обьектов.
	void Game_init() {
		SetPlayer({ 200, 200 }, 10, 10, YELLOW, 92, 100);
		CreateUI({ 0, 680 }, { 10, 20 }, 960, 40, GRAY, "0");
		this->index_health_ui = Elements.size() - 1;
		CreateEnemy({ 400, 30 }, 50, 50, RED, 100, 1, 0.5);
		CreateEnemy({ 100, 300 }, 50, 50, RED, 100, 1, 0.5);
		CreateEnemy({ 700, 200 }, 50, 50, RED, 100, 1, 0.5);
		CreateWall({ 100, 500 }, 700, 100, ORANGE);
	}

	//главное обновление движка (фунция вызвана в main)
	void Game_update() {
		player->Update_player();
		Collision_update();
		Bullet_update();
		Wall_update();
		Enemy_update();
		Custom_update();
		UI_update();
	}

};


//Создание обьекта
extern Game game;