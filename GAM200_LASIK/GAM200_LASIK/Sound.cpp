/**************************************************************************************
 *	File Name        : Sound.cpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Doyeong Yi
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#include "Sound.hpp"

extern SoundManager* SOUNDMANAGER = nullptr;
SoundManager::SoundManager()
{
	std::cout << "SoundManager Add Successful" << std::endl;
	SOUNDMANAGER = this;
	Initialize();
}

SoundManager::~SoundManager()
{
	system->release();
	system->close();
}

void SoundManager::Initialize()
{
	result = FMOD::System_Create(&system);
	ErrorCheck(result);

	result = system->init(36, FMOD_INIT_NORMAL, 0);
	ErrorCheck(result);
}

void SoundManager::Update(float /*dt*/)
{
	if (soundState == true)
	{
		result = system->update();
	}
}

void SoundManager::Shutdown()
{
	DeleteAllSounds();
}

void SoundManager::ErrorCheck(FMOD_RESULT result_)
{
	if (result_ != FMOD_OK)
	{
		exit(-1);
	}
}

void SoundManager::LoadFile(std::string filename)
{
	std::string path = "../assets/" + filename;

	FMOD::Sound* sound = NULL;
	FMOD::Channel* channel = NULL;

	Sounds.push_back(sound);
	Channels.push_back(channel);

	system->createSound(path.c_str(), FMOD_2D, NULL, &Sounds[soundID]);
	soundID++;
	ErrorCheck(result);
}

void SoundManager::PlaySound(bool loop, int ID)
{
	if (soundState == true)
	{
		if (loop == false)
		{
			Sounds[ID]->setMode(FMOD_LOOP_OFF);
		}
		else
		{
			Sounds[ID]->setMode(FMOD_LOOP_NORMAL);
		}
		Channels[ID]->setVolume(systemVolume);
		result = system->playSound(Sounds[ID], NULL, false, &Channels[ID]);
		
		bool isPlaying;
		Channels[ID]->isPlaying(&isPlaying);

		ErrorCheck(result);
	}
}

void SoundManager::DeleteAllSounds()
{
	for (auto iSound : Sounds)
	{
		result = iSound->release();

		ErrorCheck(result);
	}
	if (Sounds.size() > 0)
	{
		Sounds.erase(Sounds.begin(), Sounds.end());
	}
	if (Channels.size() > 0)
	{
		Channels.erase(Channels.begin(), Channels.end());
	}
	Sounds.clear();
	Channels.clear();

	soundID = 0;
}

void SoundManager::SoundOnOff()
{
	if (soundState == true)
	{
		soundState = false;
	}
	else
	{
		soundState = true;
	}
	ErrorCheck(result);
}

void SoundManager::StopSound(unsigned int ID)
{
	if (soundState == true)
	{
		Channels[ID]->setPaused(true);
		ErrorCheck(result);
	}
}

void SoundManager::Resume(unsigned int ID)
{
	if (soundState == true)
	{
		Channels[ID]->setPaused(false);
		ErrorCheck(result);
	}
}

void SoundManager::AllSoundStop()
{
	if (soundState == true)
	{
		for (auto ch : Channels)
		{
			ch->setPaused(true);
			ErrorCheck(result);
		}
	}
}

void SoundManager::AllResume()
{
	if (soundState == true)
	{
		for (auto ch : Channels)
		{
			ch->setPaused(false);
			ErrorCheck(result);
		}
	}
}

void SoundManager::SetSystemSoundVolume(float volume)
{
	systemVolume = volume;
	for (auto ch : Channels)
	{
		ch->setVolume(systemVolume);
		ErrorCheck(result);
	}
}
