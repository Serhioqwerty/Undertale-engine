#include <raylib.h>
#include <vector>
#include "Engine/Game.h"

Wall* wall;

void Game::Game_init() {
	InitWindow(960, 720, "Shooter game"); // Иницизилизация окна
	InitAudioDevice(); // Иницилизация аудио
	SetTargetFPS(60); // Иницилизация ФПС
	srand(static_cast<unsigned int>(time(nullptr))); // Иницилизация рандома
	SetPlayer({ 200, 200 }, 10, 10, YELLOW, 92, 1, Type_player::DEFAULT);
	CreateUI({ 0, 680 }, { 10, 20 }, 960, 40, GRAY, "0");
	this->index_health_ui = Elements.size() - 1;
	CreateEnemy({ 400, 30 }, 50, 50, RED, 100, 1, 0.1, Type_attack::TRIPLE, "");
	CreateEnemy({ 100, 300 }, 50, 50, RED, 100, 1, 0.5, Type_attack::DEFAULT, 0);
	CreateEnemy({ 700, 200 }, 50, 50, RED, 100, 1, 0.5, Type_attack::DEFAULT, 0);
	wall = CreateWallWithPointer({ 100, 500 }, 700, 100, ORANGE);
}