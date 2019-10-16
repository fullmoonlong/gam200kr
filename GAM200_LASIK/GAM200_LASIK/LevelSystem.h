#pragma once

class LevelSystem
{
public:
	//virtual void Load() = 0; //File I/O
	//virtual void Save() = 0; //File I/O
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;
};