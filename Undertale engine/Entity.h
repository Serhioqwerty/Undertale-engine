#pragma once
#include <cmath>
#include <raylib.h>
#include "Player.h"

struct Object {
	Vector2 Pos;
	float w, h;
	Color color;
};

class Entity {
private:
	Vector2 Position;
	float Width, Height;
	Color color;
public:

	Entity(Vector2 pos, float W, float H, Color c) : Position(pos), Width(W), Height(H), color(c) {
		
	}
	Entity() : Position({0, 0}), Width(10), Height(10), color(10) {

	}
	~Entity() {
		
	}
	Vector2 GetPos() {
		return this->Position;
	}
	Object GetStatus() {
		return { this->Position, this->Width, this->Height, this->color};
	}

	void Move(float dx, float dy) {
		this->Position.x += dx;
		this->Position.y += dy;
	}
	void Render() {
		DrawRectangle(this->Position.x, this->Position.y, this->Width, this->Height, this->color);
	}
	Rectangle GetRec() {
		return { this->Position.x, this->Position.y, this->Width, this->Height };
	}
	void SetPos(Vector2 pos) {
		this->Position.x = pos.x;
		this->Position.y = pos.y;
	}
};