/**************************************************************************************
 *	File Name        : Sound.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#ifndef BG_SOUNDMANAGER_H
#define BG_SOUNDMANAGER_H

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <assert.h>

#include "System.h"
#include "fmod.h"
#include "fmod.hpp"

class SoundManager : public System {
public:
	SoundManager();
	~SoundManager();

	void Initialize() override;
	void Update(float dt) override;
	void Shutdown();
	void ErrorCheck(FMOD_RESULT result_);

	void LoadFile(std::string filename);
	void PlaySound(bool loop, int ID);
	void DeleteAllSounds();

	void SoundOnOff();
	void StopSound(unsigned int ID);
	void Resume(unsigned int ID);
	void AllSoundStop();
	void AllResume();
	void SetSystemSoundVolume(float volume);

private:
	std::vector<FMOD::Sound*> Sounds;
	std::vector<FMOD::Channel*> Channels;

	FMOD::System *system;
	FMOD_RESULT result;

	float systemVolume = 1.f;
	int soundID = 0;
	unsigned int version;
	bool soundState = true;
};

extern SoundManager* SOUNDMANAGER;
#endif