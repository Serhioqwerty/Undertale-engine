#include <raylib.h>
#include <string>
#include "Engine/UI.h"

Element::Element(Vector2 pos_box, Vector2 pos_text, float W, float H, Color c, const char* t) : position_box(pos_box), position_text(pos_text), Width(W), Height(H), color(c) {
	this->text = t;
	this->Size_font = 12;
	this->color_text = WHITE;
}

Element::~Element(){
	
}

void Element::SetText(const char* t) {
	this->text = t;
}

void Element::SetSizeFont(int p) {
	this->Size_font = p;
}

void Element::SetPosition(Vector2 pos) {
	this->position_box = pos;
}

void Element::SetColorText(Color c) {
	this->color_text = c;
}

void Element::Render() {
	DrawRectangle(this->position_box.x, this->position_box.y, this->Width, this->Height, this->color);
	DrawText(text.c_str(), this->position_box.x + this->position_text.x, this->position_box.y + this->position_text.y, this->Size_font, this->color_text);
}