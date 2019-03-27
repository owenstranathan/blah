#ifndef AABB_HPP
#define AABB_HPP

#include <iostream>
#include <SFML/System.hpp>

#include "whatever.hpp"

namespace blah {


	class AxisAlignedBoundingBox {
	public:
		AxisAlignedBoundingBox() : particle(nullptr){}
		AxisAlignedBoundingBox(Particle* p);
	    ~AxisAlignedBoundingBox(){ }

		sf::Vector2f min();
		sf::Vector2f max();

		const Particle* particle;
	};
	
	
	typedef AxisAlignedBoundingBox AABB;

}

std::ostream &operator<<(std::ostream&, blah::AABB&);

#endif // !AABB_HPP
