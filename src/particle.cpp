#include <string>

#include "particle.hpp"
#include "whatever.hpp"
#include "ovector.hpp"
#include "aabb.hpp"

namespace blah {
	Particle::Particle() : position(sf::Vector2f()),
		velocity(sf::Vector2f()),
		acceleration(sf::Vector2f()),
		origin(sf::Vector2f()),
		primaryColor(sf::Color::Transparent),
		secondaryColor(sf::Color::Black),
		id(++particle_ids)
	{
		sf::Text text(std::to_string(id), font, 10); // TODO: make font size a member
		aabb.particle = this;
		shape = sf::CircleShape(radius, vertices);
		origin = sf::Vector2f(radius, radius);
		shape.setFillColor(primaryColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(secondaryColor);
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		text.setFont(font);
		text.setCharacterSize(10);
		text.setStyle(sf::Text::Regular);
		text.setFillColor(secondaryColor);
	}

	Particle::Particle(sf::Vector2f & p, float r) : position(p),
		radius(r),
		primaryColor(sf::Color::Transparent),
		secondaryColor(sf::Color::Black),
		id(++particle_ids)
	{
		sf::Text text(std::to_string(id), font, 10); // TODO: make font size a member
		aabb.particle = this;
		shape = sf::CircleShape(radius, vertices);
		origin = sf::Vector2f(radius, radius);
		shape.setFillColor(primaryColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(secondaryColor);
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		text.setFont(font);
		text.setCharacterSize(10);
		text.setStyle(sf::Text::Regular);
		text.setFillColor(secondaryColor);
	}

	int Particle::particle_ids = 0;
	sf::Font Particle::font = sf::Font();

	Particle::~Particle()
	{
	}

	void Particle::updateShape() {
	}

	void Particle::draw(sf::RenderTarget &rt)
	{
		text.setPosition(position);
		text.setFillColor(secondaryColor);
		text.setCharacterSize(10);	
		text.setFont(font);
		shape.setPosition(position);
		shape.rotate(-90 * deltaTime.count());
		rt.draw(shape);
		rt.draw(text);
	}


	bool Particle::collision(const Particle &p)
	{
		sf::Vector2f relativePosition = position - p.position;
		double distanceSquared = squareMagnitude(relativePosition);
		double squareCollisionRadius = std::pow((radius + p.radius), 2);
		return distanceSquared < squareCollisionRadius;
	}

	void Particle::collide(const Particle &p)
	{
		sf::Vector2f relativePosition = position - p.position;
		sf::Vector2f relativeCollisionPoint = normalized(relativePosition) * radius;
		sf::Vector2f collisionPoint = position + relativeCollisionPoint;
		auto radii = radius + p.radius;
		sf::Vector2f correctiveForce = normalized(collisionPoint - p.position) * std::abs(magnitude(relativePosition) - radii);
		velocity += correctiveForce;
	}

	void Particle::kinematics()
	{
		if (velocity.x > 1.0f)
			velocity.x = 1.0f;
		if (velocity.y > 1.0f)
			velocity.y = 1.0f;

		position += velocity;
		velocity += acceleration;
		acceleration = sf::Vector2f();

		if (aabb.min().x < 0)
		{
			Particle fakey = Particle();
			fakey.position.x = aabb.min().x;
			fakey.position.y = position.y;
			fakey.radius = std::abs(aabb.min().x);
			collide(fakey);
		}
		else if (aabb.max().x > SCREEN_WIDTH)
		{
			Particle fakey = Particle();
			fakey.position.x = aabb.max().x;
			fakey.position.y = position.y;
			fakey.radius = std::abs(aabb.max().x - SCREEN_WIDTH);
			collide(fakey);
		}
		if (aabb.min().y < 0)
		{
			Particle fakey = Particle();
			fakey.position.x = position.x;
			fakey.position.y = aabb.min().y;
			fakey.radius = std::abs(aabb.min().y);
			collide(fakey);
		}
		else if (aabb.max().y > SCREEN_HEIGHT)
		{
			Particle fakey = Particle();
			fakey.position.x = position.x;
			fakey.position.y = aabb.max().y;
			fakey.radius = std::abs(aabb.max().y - SCREEN_HEIGHT);
			collide(fakey);
		}
	}

	void Particle::resolveCollision(Particle& a, Particle& b) {
		if (a.collision(b)) {
			a.collide(b);
			b.collide(a);
		}
	}

	void Particle::loadStatic() {
		font.loadFromFile("IBMPlexMono-Regular.ttf");
	}

	Particle * randomParticle()
	{
		Particle* p = new Particle(randomVector2<float>(), randomNumber<float>(1, 30));
		p->velocity = randomVector2<float>(0.0f, 5.0f);
		return p;
	}

	
}