#ifndef SAP_HPP
#define SAP_HPP

#include <vector>
#include "whatever.hpp"
#include "particle.hpp"


namespace blah {


	class SweepAndPrune {
	public:
		SweepAndPrune();
		void addParticle(Particle *);
		void resolveCollisions();

	private:
		std::vector<Particle *>   xAxis;
		std::vector<std::pair<Particle*, Particle*>> pairs;
	};

	typedef SweepAndPrune SAP;
}
#endif // !SAP_HPP
