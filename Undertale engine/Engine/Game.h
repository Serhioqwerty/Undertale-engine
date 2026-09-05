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

	//функции
	//функция иницилизации игрока
	void SetPlayer(Vector2 pos, float W, float H, Color c, float health, int exp, Type_player type);

	//обновление памяти (заброшено)
	void UpdateRam();

	//создание UI
	void CreateUI(Vector2 pos_box, Vector2 pos_text, float W, float H, Color c, const char* t);

	//обновление твердых коллизий
	void Col_update(Rectangle& hitbox_object);

	//создание обьекта с твердыми колизиями
	Wall* CreateWallWithPointer(Vector2 pos, float W, float H, Color c);
	int CreateWallWithIndex(Vector2 pos, float W, float H, Color c);
	void CreateWall(Vector2 pos, float W, float H, Color c);

	//обновление колизий у пуль
	void Collision_update();
	//создание врага
	void CreateEnemy(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta, Type_attack t, const char* texture);
	Enemy* CreateEnemyWithPointer(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta, Type_attack t, const char* texture);
	int CreateEnemyWithIndex(Vector2 pos, float W, float H, Color c, float Health, float Attack, float ta, Type_attack t, const char* texture);

	Wall* GetWallPointer(int index); //Получение стены
	Wall* GetLastWallPointer(); //Получение последней стены


	bool RayCasting(Vector2& enemy, float distance);

	//Обновление врагов
	void Enemy_update();
	//Обновление пуль
	void Bullet_update();

	//Обновление UI
	void UI_update();

	//Удаление стены

	void DeleteWallWithIndex(int index); //Удаление стены с помощью индекса
	void DeleteWallWithPointer(Wall* ptr); //Удаление стены с помощью указателя
	void DeleteAllWalls(); //Удаление всех стен
	void DeleteWallWithSmartPointer(std::unique_ptr<Wall>& smart_ptr); //Удаление стеаны с помощью умного указателя


	//Удаление врагов

	void DeleteEnemyWithIndex(int index); //Удаление врагов с помощью индекса
	void DeleteEnemyWithPointer(Enemy* ptr); //Удаление врагов с помощью указателя
	void DeleteAllEnemys(); //Удаление всех врагов
	void DeleteEnemyWithSmartPointer(std::unique_ptr<Enemy>& smart_ptr); //Удаление врага с помощью умного указателя

	

	//Обновление аудио

	//Обновление стены, включающая обновление твердых коллизий
	void Wall_update();
public:
	//массивы
	std::vector<std::unique_ptr<Bullet>>Bullets;
	std::unique_ptr<Player>player;
	std::vector<std::unique_ptr<Enemy>>Enemys;
	std::vector<std::unique_ptr<Element>>Elements;
	std::vector<std::unique_ptr<Wall>>Walls;

	Game() : RAM(0) {

	}




	//Пользовательское обновление, где программист сможет добавлять свое
	void Custom_update();

	//Иницилизация игры. Нужна для певроначального создания обьектов.
	void Game_init();

	//главное обновление движка (фунция вызвана в main)
	void Game_update();

};


//Создание обьекта
extern Game game;