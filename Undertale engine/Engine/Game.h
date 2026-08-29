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
	void SetPlayer(Vector2 pos, float W, float H, Color c, float health, int exp);

	//обновление памяти (заброшено)
	void UpdateRam();

	//создание UI
	void CreateUI(Vector2 pos_box, Vector2 pos_text, float W, float H, Color c, const char* t);

	//обновление твердых коллизий
	void Col_update(Rectangle& hitbox_object);

	//создание обьекта с твердыми колизиями
	void CreateWall(Vector2 pos, float W, float H, Color c);

	//обновление колизий у пуль
	void Collision_update();
	//создание врага
	void CreateEnemy(Vector2 pos, float W, float H, Color c, float Health, float Attack, float t, Type_attack type);
	
	bool RayCasting(Vector2& enemy, float distance);

	//Обновление врагов
	void Enemy_update();
	//Обновление пуль
	void Bullet_update();

	//Обновление UI
	void UI_update();

	//Обновление стены, включающая обновление твердых коллизий
	void Wall_update();

	
	//Пользовательское обновление, где программист сможет добавлять свое
	void Custom_update();

	//Иницилизация игры. Нужна для певроначального создания обьектов.
	void Game_init();

	//главное обновление движка (фунция вызвана в main)
	void Game_update();

};


//Создание обьекта
extern Game game;