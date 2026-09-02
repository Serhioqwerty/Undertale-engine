#include "Engine/Audio.h"
#include <raylib.h>

    Audio_class::~Audio_class() {
	 UnloadMusicStream(music);
	 UnloadSound(sound);
	}

void Audio_class::Play_sound(const char* path) {
	this->sound = LoadSound(path);
	PlaySound(sound);
}

void Audio_class::Play_music(const char* path) {
	this->music = LoadMusicStream(path);
	PlayMusicStream(this->music);
	this->Lenght = GetMusicTimeLength(this->music);
	this->Is_loop = false;
	this->Is_work = true;
}

void Audio_class::Play_music_loop(const char* path) {
	this->music = LoadMusicStream(path);
	PlayMusicStream(this->music);
	this->Lenght = GetMusicTimeLength(this->music);
	this->Is_loop = true;
	this->Is_work = true;
}

info_audio Audio_class::GetInfo() {
	return { music, sound };
}

void Audio_class::Audio_update_engine() {
	UpdateMusicStream(this->music);
}

Music* Audio_class::GetPointerMusic() {
	return &this->music;
}

void Audio_class::Update_music() {
	Audio_update_engine();
	if (Is_work == true) {
		//std::cout << "current: " << this->CurrentTime << "Lenght: " << this->Lenght << std::endl;
		this->CurrentTime = GetMusicTimePlayed(this->music);
		if (Is_loop == false) {
			if (this->CurrentTime >= this->Lenght - 0.1) {
				std::cout << "Pause!" << std::endl;
				UnloadMusicStream(this->music);
				this->Is_work = false;
			}
		}
	}
}
