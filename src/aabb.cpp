
#include "whatever.hpp"
#include "aabb.hpp"
#include "particle.hpp"

namespace blah {

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(Particle* p) {
		particle = p;
	}

	sf::Vector2<float> AxisAlignedBoundingBox::min() {
		return sf::Vector2<float>(particle->position.x - particle->radius, particle->position.y - particle->radius);
	}

	sf::Vector2<float> AxisAlignedBoundingBox::max() {
		return sf::Vector2<float>(particle->position.x + particle->radius, particle->position.y + particle->radius);
	}
}