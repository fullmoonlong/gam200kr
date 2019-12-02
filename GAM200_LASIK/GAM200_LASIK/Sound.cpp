#include "Sound.hpp"


extern SoundManager* SOUNDMANAGER = nullptr;
SoundManager::SoundManager()
{
	std::cout << "SoundManager Add Successful" << std::endl;
	SOUNDMANAGER = this;
}

SoundManager::~SoundManager()
{
	system->release();
	system->close();
}

void SoundManager::Initialize()
{
	result_ = FMOD::System_Create(&system);
	ErrorCheck(result_);

	result_ = system->init(36, FMOD_INIT_NORMAL, 0);
	ErrorCheck(result_);
}

void SoundManager::Update()
{
	if (soundState == true)
	{
		result_ = system->update();
	}
}

void SoundManager::Shutdown()
{
}

void SoundManager::ErrorCheck(FMOD_RESULT /*result*/)
{
	//assert(result == FMOD_OK);
}

void SoundManager::LoadFile(std::string filename)
{
	std::string path = "../assets/" + filename;

	FMOD::Sound* sound = 0;
	FMOD::Channel* channel = 0;

	Sounds.push_back(sound);
	Channels.push_back(channel);
	FMOD_RESULT volume_ = Channels[soundID]->setVolume(1.f);
	Volume.push_back((float)volume_);

	result_ = system->createSound(path.c_str(), FMOD_2D, 0, &Sounds[soundID]);
	//added = true;
	soundID++;
	ErrorCheck(result_);
}

void SoundManager::PlaySound(bool loop, unsigned int ID)
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
		result_ = system->playSound(Sounds[ID], NULL, false, &Channels[ID]);

		bool isPlaying = false;
		Channels[ID]->isPlaying(&isPlaying);

		ErrorCheck(result_);
	}
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
	ErrorCheck(result_);
}

void SoundManager::Stop(unsigned int ID)
{
	if (soundState == true)
	{
		Channels[ID]->setPaused(true);
		ErrorCheck(result_);
	}
}

void SoundManager::Resume(unsigned int ID)
{
	if (soundState == true)
	{
		Channels[ID]->setPaused(false);
		ErrorCheck(result_);
	}
}

void SoundManager::AllStop()
{
	for (auto ch : Channels)
	{
		ch->setPaused(true);
		ErrorCheck(result_);
	}
}

void SoundManager::AllResume()
{
	for (auto ch : Channels)
	{
		ch->setPaused(false);
		ErrorCheck(result_);
	}
}

void SoundManager::SetSystemSoundVolume(float volume)
{
	for (auto ch : Channels)
	{
		ch->setVolume(volume);
		ErrorCheck(result_);
	}
}
