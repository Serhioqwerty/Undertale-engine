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
	Texture2D texture;
	bool is_texture;
public:

	Entity(Vector2 pos, float W, float H, Color c) : Position(pos), Width(W), Height(H), color(c) {
		this->is_texture = false;
	}
	Entity(Vector2 pos, float W, float H, Color c, const char* texture_path) : Position(pos), Width(W), Height(H), color(c) {
		this->texture = LoadTexture(texture_path);
		if (this->texture.id == 0) {
			this->is_texture = false;
		}
		else {
			this->is_texture = true;
		}

	}
	Entity() : Position({ 0, 0 }), Width(10), Height(10), color(10) {

	}
	~Entity() {

	}
	Vector2 GetPos() {
		return this->Position;
	}
	Object GetStatus() {
		return { this->Position, this->Width, this->Height, this->color };
	}

	void Move(float dx, float dy) {
		this->Position.x += dx;
		this->Position.y += dy;
	}

	void Update_info_texture() {
		if (this->texture.id == 0) {
			this->is_texture = false;
		}
		else {
			this->is_texture = true;
		}
	}

	void Render() {
		if (this->is_texture == 0) {
			DrawRectangle(this->Position.x, this->Position.y, this->Width, this->Height, this->color);
		}
		else if (this->is_texture == 1) {
			DrawTexturePro(this->texture, this->GetRec(), this->GetRec(), { 0, 0 }, 0, WHITE);
		}
	}
	Rectangle GetRec() {
		return { this->Position.x, this->Position.y, this->Width, this->Height };
	}
	void SetPos(Vector2 pos) {
		this->Position.x = pos.x;
		this->Position.y = pos.y;
	}
	void SetTexture(const char* texture_path) {
		this->texture = LoadTexture(texture_path);

	}
};