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
		Particle(sf::Vector2f &, float);
		~Particle();

		void draw(sf::RenderTarget &);
		void kinematics();
		bool collision(const Particle &);
		void collide(const Particle &);
		void updateShape();
		static void resolveCollision(Particle&, Particle&);
		// static void loadStatic();


		static int particle_ids;

		int id;
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		sf::Vector2f origin;
		sf::Color primaryColor;
		sf::Color secondaryColor;
		sf::CircleShape shape;
		sf::Text text;
		sf::Font font;
		AABB aabb;
		float radius;
		float rotation;
		float outlineThickness = 1;
		float drawDistance = 200;
	};


	Particle * randomParticle(float, float);

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


