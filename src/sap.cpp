
#include <iostream>
#include "sap.hpp"
#include "ovector.hpp"
#include "particle.hpp"

namespace blah {

	SweepAndPrune::SweepAndPrune() {}

	void SweepAndPrune::addParticle(Particle * p) {
		insert_sorted(xAxis, p, [](Particle* a, Particle* b) -> bool { return a->aabb->min().x < b->aabb->min().x; });
		insert_sorted(yAxis, p, [](Particle* a, Particle* b) -> bool { return a->aabb->min().y < b->aabb->min().y; });
	}
		

	void SweepAndPrune::resolveCollisions() {
		auto sort_by_x = [](Particle * a, Particle * b) -> bool { return a->aabb->min().x < b->aabb->min().x; };
		insertion_sort<Particle *>(xAxis.begin(), xAxis.end(), sort_by_x);

		//std::vector<std::pair<Particle*, Particle*>> pairs;
		int potentionalCollisions = 0;
		std::vector<Particle *> active;
		active.push_back(xAxis[0]);
		for (auto x = std::next(xAxis.begin()); x != xAxis.end(); ++x) {
			std::vector<Particle *> stillActive;
			if (active.empty()) {
				break;
			}
			for (auto a = active.begin(); a != active.end(); ++a){
				if ((*a)->aabb->max().x > (*x)->aabb->min().x) {
					potentionalCollisions++;
					Particle::resolveCollision(*(*a), *(*x));
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
		}
	}	

}