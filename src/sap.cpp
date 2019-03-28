
#include <iostream>
#include "sap.hpp"
#include "ovector.hpp"
#include "particle.hpp"

namespace blah {

	SweepAndPrune::SweepAndPrune() {}

	void SweepAndPrune::addParticle(Particle * p) {
		insert_sorted(xAxis, p, [](Particle* a, Particle* b) -> bool { return a->aabb.min().x < b->aabb.min().x; });
		insert_sorted(yAxis, p, [](Particle* a, Particle* b) -> bool { return a->aabb.min().y < b->aabb.min().y; });
	}
		

	void SweepAndPrune::resolveCollisions() {
		auto sort_by_x = [](Particle * a, Particle * b) -> bool { return a->aabb.min().x < b->aabb.min().x; };
		insertion_sort<Particle *>(xAxis.begin(), xAxis.end(), sort_by_x);
		std::vector<std::pair<Particle*, Particle*>> xPairs;
		std::vector<Particle *> active;
		active.push_back(xAxis[0]);
		for (auto x = std::next(xAxis.begin()); x != xAxis.end(); ++x) {
			std::vector<Particle *> stillActive;
			for (auto a = active.begin(); a != active.end(); ++a){
				if ((*a)->aabb.max().x > (*x)->aabb.min().x) {
					xPairs.push_back(std::make_pair(*a, *x));
					stillActive.push_back(*a);
					if (std::find(stillActive.begin(), stillActive.end(), *x) == stillActive.end())
						stillActive.push_back(*x);
				}
				else {
					break;
				}
			}
			active.swap(stillActive);
			stillActive.clear();
			if (active.empty()) {
				active.push_back(*x);
			}
		}
		if (xPairs.size() < 1){
			return;
		}
		auto sort_by_y = [](Particle * a, Particle * b) -> bool { return a->aabb.min().y < b->aabb.min().y; };
		insertion_sort<Particle *>(yAxis.begin(), yAxis.end(), sort_by_y);
		active.clear();
		active.push_back(yAxis[0]);
		for (auto y = std::next(yAxis.begin()); y != yAxis.end(); ++y) {
			std::vector<Particle *> stillActive;
			for (auto a = active.begin(); a != active.end(); ++a) {
				if ((*a)->aabb.max().y > (*y)->aabb.min().y) {
					auto pair = std::make_pair(*a, *y);
					if (std::find(xPairs.begin(), xPairs.end(), pair) != xPairs.end()) 
						Particle::resolveCollision(**a, **y);
					stillActive.push_back(*a);
					if (std::find(stillActive.begin(), stillActive.end(), *y) == stillActive.end())
						stillActive.push_back(*y);
				}
				else {
					break;
				}
			}
			active.swap(stillActive);
			stillActive.clear();
			if (active.empty()) {
				active.push_back(*y);
			}
		}
	}	

}