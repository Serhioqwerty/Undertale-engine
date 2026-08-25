#pragma once
#include <raylib.h>
#include <string>

class Element {
private:
	Vector2 position_box;
	Vector2 position_text;
	float Width, Height;
	Color color;
	std::string text;
	int Size_font;
	Color color_text;
public:
	Element(Vector2 pos_box, Vector2 pos_text, float W, float H, Color c,  const char* t) : position_box(pos_box), position_text(pos_text), Width(W), Height(H), color(c) {
		this->text = t;
		this->Size_font = 12;
		this->color_text = WHITE;
	}
	~Element() {

	}
	void SetText(const char* t) {
		this->text = t;
	}
	void SetSizeFont(int p) {
		this->Size_font = p;
	}
	void SetPosition(Vector2 pos) {
		this->position_box = pos;
	}
	void SetColorText(Color c) {
		this->color_text = c;
	}

	void Render() {
		DrawRectangle(this->position_box.x, this->position_box.y, this->Width, this->Height, this->color);
		DrawText(text.c_str(), this->position_box.x + this->position_text.x, this->position_box.y + this->position_text.y, this->Size_font, this->color_text);
	}
};