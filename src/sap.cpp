
#include <iostream>
#include <algorithm>
#include <set>
#include "sap.hpp"
#include "ovector.hpp"
#include "particle.hpp"

namespace blah {

	SweepAndPrune::SweepAndPrune() {}

	void SweepAndPrune::addParticle(Particle * p) {
		insert_sorted(xAxis, p, [](Particle* a, Particle* b) -> bool { return a->aabb.min().x < b->aabb.min().x; });
		// insert_sorted(yAxis, p, [](Particle* a, Particle* b) -> bool { return a->aabb.min().y < b->aabb.min().y; });
	}
	
	void GetPairs(std::vector<Particle*>& particles, std::vector<std::pair<Particle*, Particle*>>& pairs) {
		std::vector<Particle*> allActive = { };
		std::vector<Particle*> active = { };
		auto by_y = [](Particle * a, Particle * b) -> bool { return a->aabb.min().y < b->aabb.min().y; };
		active.push_back(*particles.begin());
		insert_sorted(allActive, *particles.begin(), by_y);
		for (auto p = std::next(particles.begin()); p != particles.end(); ++p) {
			std::vector<Particle*> stillActive;
			auto particle = (*p);
			for (auto&& active : active) {
				if ((particle->position.x - particle->radius) < (active->position.x + active->radius)) {
					insert_sorted(allActive, active, by_y);
					stillActive.push_back(active);
				}
			}
			active.clear();
			active.swap(stillActive);
			stillActive.clear();
			active.push_back(particle);
		}

		active.clear();
		active.push_back(*allActive.begin());
		for (auto p = std::next(allActive.begin()); p != allActive.end(); ++p) {
			std::vector<Particle*> stillActive;
			auto particle = (*p);
			for (auto&& active : active) {
				if ((particle->position.y - particle->radius) < (active->position.y + active->radius)) {
				// if ((particle->position.x - particle->radius) < (active->position.x + active->radius)) {
					auto pair = (particle->id < active->id) ? std::make_pair(particle, active) : std::make_pair(active, particle);
					pairs.push_back(pair);
					stillActive.push_back(active);
				}
			}
			active.clear();
			active.swap(stillActive);
			stillActive.clear();
			active.push_back(particle);
		}
	}


	template<typename Pred>
	void GetPairsForAxis(std::vector<Particle*> axis, std::vector<std::pair<Particle*, Particle*>>& pairs, Pred predicate) {
		std::vector<Particle*> activeParticles;
		activeParticles.push_back(*axis.begin());
		for (auto p = std::next(axis.begin()); p != axis.end(); ++p) {
			std::vector<Particle*> stillActive;
			auto particle = (*p);
			for (auto&& active : activeParticles) {
				if ((predicate(particle) - particle->radius) < (predicate(active) + active->radius)) {
					auto pair = (particle->id < active->id) ? std::make_pair(particle, active) : std::make_pair(active, particle);
					pairs.push_back(pair);
					stillActive.push_back(active);
				}
			}
			activeParticles.clear();
			activeParticles.swap(stillActive);
			stillActive.clear();
			activeParticles.push_back(particle);
		}
	}

	void GetPairsForAxis(std::vector<Particle*> axis, std::vector<std::pair<Particle*, Particle*>>& pairs) {
		std::vector<Particle*> activeParticles;
		activeParticles.push_back(*axis.begin());
		for (auto p = std::next(axis.begin()); p != axis.end(); ++p) {
			std::vector<Particle*> stillActive;
			auto particle = (*p);
			for (auto&& active : activeParticles) {
				if (dot2(particle->aabb.min(), sf::Vector2f(1,0)) < dot2(active->aabb.max(), sf::Vector2f(1,0))){ // I think I like the dot version best
					auto pair = (particle->id < active->id) ? std::make_pair(particle, active) : std::make_pair(active, particle);
					pairs.push_back(pair);
					stillActive.push_back(active);
				}
			}
			activeParticles.clear();
			activeParticles.swap(stillActive);
			stillActive.clear();
			activeParticles.push_back(particle);
		}
	}



	void SweepAndPrune::resolveCollisions() {
	 	insertion_sort<Particle *>(xAxis.begin(), xAxis.end(), [](Particle * a, Particle * b) -> bool { return a->aabb.min().x < b->aabb.min().x; });
		pairs.clear();
		GetPairsForAxis(xAxis, pairs, [](Particle * p) -> float {return p->position.x; });
		for (auto&& pair : pairs) {
			if (pair.first->collision(*pair.second)) {
				pair.first->collide(*pair.second);
				pair.second->collide(*pair.first);
			}
		}
		
	}	
}