#ifndef WHATEVER_HPP
#define WHATEVER_HPP


#include <random>
#include <functional>
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

	template <typename T, typename Iter, typename Pred>
	void insertion_sort(Iter begin, Iter end, Pred predicate) {
		for (auto it = begin; it != end; ++it) {
			std::rotate(std::upper_bound(begin, it, *it, predicate), it, std::next(it)); 
		}
	}

	template <typename T, typename Pred>
	typename std::vector<T>::iterator insert_sorted(std::vector<T> &v, T item, Pred predicate) {
		return v.insert(
			std::upper_bound(v.begin(), v.end(), item, predicate),
			item
		);
	}

} // namespace blah

#endif // !WHATEVER_HPP
