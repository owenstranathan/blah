#ifndef WHATEVER_HPP
#define WHATEVER_HPP


#include <random>
#include <chrono>

extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
extern std::chrono::duration<float> deltaTime;

namespace blah
{

	// Classes
	class Particle;
	class AxistAlignedBoundingBox;



	template <typename T>
	T randomNumber(T start, T end)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<T> dist(start, end);
		return (T)dist(gen);
	}

} // namespace blah

#endif // !WHATEVER_HPP
