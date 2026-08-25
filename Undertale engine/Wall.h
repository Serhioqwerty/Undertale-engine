#pragma once
#include <raylib.h>
#include "Enemy.h"

class Wall : public Entity{
private:
public:
	Wall(Vector2 pos, float W, float H, Color c) : Entity(pos, W, H, c) {}
	~Wall() {

	}
};