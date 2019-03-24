#ifndef AABB_HPP
#define AABB_HPP


#include <SFML/System.hpp>
#include "whatever.hpp"

namespace blah {

	class AxisAlignedBoundingBox {
	public:
		AxisAlignedBoundingBox() : particle(nullptr){}
		AxisAlignedBoundingBox(Particle* p);
	    ~AxisAlignedBoundingBox(){ }

		sf::Vector2<float> min();
		sf::Vector2<float> max();

		const Particle* particle;
	};
	
}

#endif // !AABB_HPP
