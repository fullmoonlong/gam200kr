/*
 *	Author: JeongHak Kim	junghak.kim@digipen.edu
 *	
 *	File_name: Clock.hpp
 *	
 *	Clock class that helps calculate time
 *	
 *	2019/10/31
 */

#pragma once
#include <chrono>

class Clock
{
public:
	using time = std::chrono::system_clock;
	using second = std::chrono::duration<float, std::ratio<1000>>;

	Clock() noexcept
		: timeStamp(time::now()) {}
	void UpdateTime() noexcept
	{
		timeStamp = time::now();
	}
	float GetTimeBySecond() const noexcept
	{
		return std::chrono::duration_cast<second>(time::now() - timeStamp).count();
	}
	float GetDeltaTime() const noexcept
	{
		return std::chrono::duration<float>(time::now() - timeStamp).count();
	}
private:
	time::time_point timeStamp;
};
