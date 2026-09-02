#pragma once
#include "Entity.h"
#include "Enemy.h"

enum class Type_player {DEFAULT, PHYSIC};


class Player : public Entity {
private:

	Type_player type_player;
	float health;
	int lvl;
	int exp;
	float speed;
	Vector2 vector_move;
	Vector2 old_pos;
	const float gravity = 9.8;
	bool is_gravity;
public:
	int GetLvl(); //Получение уровня
	Player(Vector2 vec, float Width, float Height, float health, int exp, Color color, Type_player type);
	
	void GetEX(unsigned int exp); //Добавление опыта
	

	void Update_player(); //Обновление игрока
		
	
	void Attack(float h); //Получить урон
	void SetHealth(float h); //Изменить здоровья
	float GetHealth(); //Получить здоровье
	Vector2 GetOldPos(); //Получить старую позицию
};
