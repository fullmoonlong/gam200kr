/*
*	Author: Doyeong Yi doyoung.lee@digipen.edu
*	GAM200 Engine Prototype
*	2019/11/08
*/
#pragma once
#ifndef BG_SOUNDMANAGER_H
#define BG_SOUNDMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

#include "System.h"
#include "fmod.hpp"
#include "fmod.h"

class SoundManager : public System {
public:
	SoundManager();
	~SoundManager();

	void Initialize() override;
	void Update(float dt) override;
	void Shutdown();
	void ErrorCheck(FMOD_RESULT result);

	void LoadFile(std::string filename);
	void PlaySound(bool loop, unsigned int ID);

	//need to modify
	void SoundOnOff();
	void Stop(unsigned int ID);
	void Resume(unsigned int ID);
	void AllStop();
	void AllResume();
	void SetSystemSoundVolume(float volume);
	//need to modify

	std::vector<float> Volume;
private:
	std::vector<FMOD::Sound*> Sounds;
	std::vector<FMOD::Channel*>Channels;
	FMOD::System *system;
	FMOD_RESULT result_;

	unsigned int soundID = 0;
	bool added = false;
	unsigned int version;
	bool soundState = true;
	bool loopState;
};

extern SoundManager* SOUNDMANAGER;
#endif