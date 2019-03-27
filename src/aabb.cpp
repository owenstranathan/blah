
#include "whatever.hpp"
#include "aabb.hpp"
#include "particle.hpp"
#include "ovector.hpp"

namespace blah {

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(Particle* p) {
		particle = p;
	}

	sf::Vector2f AxisAlignedBoundingBox::min() {
		return sf::Vector2f(particle->position.x - particle->radius, particle->position.y - particle->radius);
	}

	sf::Vector2f AxisAlignedBoundingBox::max() {
		return sf::Vector2f(particle->position.x + particle->radius, particle->position.y + particle->radius);
	}
	
}

std::ostream & operator<<(std::ostream& os, blah::AABB& aabb) {
	os << aabb.min() << ", " << aabb.max();
	return os;
}
