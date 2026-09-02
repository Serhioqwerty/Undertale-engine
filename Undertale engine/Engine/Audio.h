#pragma once
#include <raylib.h>
#include <iostream>

struct info_audio {
	Music music;
	Sound sound;
};

class Audio_class {
private:
	Music music;
	Sound sound;
	float Lenght;
	float CurrentTime;
	bool Is_loop;
	bool Is_work;
	int count;
public:  

	Audio_class() : Lenght(0), CurrentTime(0) {}

	void Play_sound(const char* path); //Проиграть звук
	void Play_music(const char* path); //Проиграть музыку
	void Play_music_loop(const char* path); //Проиграть музыку с повторением
	void Audio_update_engine(); //Обновление аудио
	void Update_music(); //Обновление буфера музыки

	~Audio_class(); //Деструктор
	
	info_audio GetInfo(); //Получение информации о музыке и звуке

	Music* GetPointerMusic(); //Получение адреса музыки
	
};
