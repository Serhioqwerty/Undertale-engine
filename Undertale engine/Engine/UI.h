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
	std::string class_ui;
public:
	Element(Vector2 pos_box, Vector2 pos_text, float W, float H, Color c, const char* t);
	~Element();

	void SetText(const char* t); //Изменить текст
	void SetSizeFont(int p); //Изменить размер шрифта
	void SetPosition(Vector2 pos); //Изменить позицию
	void SetColorText(Color c); //Изменить цвет текста

	void Render(); //Отрендерить
};