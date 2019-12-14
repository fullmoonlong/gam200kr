/**************************************************************************************
 *	File Name        : Clock.hpp
 *	Project Name     : Keyboard Warriors
 *	Primary Author   : Jeonghak Kim
 *	Secondary Author :
 *	Copyright Information :
 *    "All content 2019 DigiPen (USA) Corporation, all rights reserved."
 **************************************************************************************/

#pragma once
#include <chrono>

class Clock
{
public:
	using time = std::chrono::high_resolution_clock;
	using second = std::chrono::duration<float>;

	Clock() noexcept
		: timePassed(0), timeStamp(time::now()) {}
	void UpdateClock() noexcept
	{
		timePassed += GetTimeFromLastUpdate();
		timeStamp = time::now();
	}
	
	float GetTimeFromLastUpdate() const noexcept
	{
		return std::chrono::duration<float>(time::now() - timeStamp).count();
	}
public:
	float timePassed;
private:
	time::time_point timeStamp;
};
