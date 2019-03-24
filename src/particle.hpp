#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "whatever.hpp"
#include "aabb.hpp"


namespace blah
{


	class Particle
	{
	public:
		Particle();
		// Particle(const sf::Vector2<double> &);
		~Particle();

		void draw(sf::RenderTarget &);
		void kinematics();
		bool collision(const Particle &);
		void collide(const Particle &);


		sf::Vector2<float> position;
		sf::Vector2<float> velocity;
		sf::Vector2<float> acceleration;
		sf::Color primaryColor;
		sf::Color secondaryColor;
		sf::CircleShape shape;
		AxisAlignedBoundingBox* aabb;
		float radius;
		float rotation;
		float outlineThickness = 1;
		float drawDistance = 200;
		int vertices = 7;
	};


	Particle * randomParticle();

} // namespace blah

template <typename T>
std::ostream &operator<<(std::ostream &os, blah::Particle &p)
{
    os << "Pos: " << p.position << std::endl
       << "Vel: " << p.velocity << std::endl
       << "Radius: " << p.radius << std::endl;
    return os;
}

#endif


