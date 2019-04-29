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
		aabb.particle = this;
		shape = sf::CircleShape(radius);
		origin = sf::Vector2f(radius, radius);
		shape.setFillColor(primaryColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(secondaryColor);
		shape.setRadius(radius);
		//shape.setOrigin(radius, radius);
		//font.loadFromFile("IBMPlexMono-Regular.ttf");
		text.setFont(font);
		text.setString(std::to_string(id));
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
		aabb.particle = this;
		shape = sf::CircleShape(radius);
		origin = sf::Vector2f(radius, radius);
		shape.setFillColor(primaryColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(secondaryColor);
		shape.setRadius(radius);
		//shape.setOrigin(radius, radius);
		// font.loadFromFile("IBMPlexMono-Regular.ttf");
		text.setFont(font);
		text.setString(std::to_string(id));
		text.setCharacterSize(10);
		text.setStyle(sf::Text::Regular);
		text.setFillColor(secondaryColor);
	}

	int Particle::particle_ids = 0;

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
		//text.setFont(font);
		// sf::CircleShape min = sf::CircleShape(1);
		// min.setPosition(aabb.min());
		// min.setFillColor(sf::Color::Red);
		// min.setOutlineColor(sf::Color::Red);
		// sf::CircleShape max = sf::CircleShape(1);
		// max.setPosition(aabb.max());
		// max.setFillColor(sf::Color::Red);
		// max.setOutlineColor(sf::Color::Red);
		// sf::Vector2f rectPos(position.x - radius, position.y - radius);
		// sf::Vector2f rectSize(2 * radius, 2 * radius);
		// sf::Rect<float> rect(rectPos, rectSize);
		// sf::RectangleShape rectShape(rectSize);
		// rectShape.setPosition(rectPos);
		// rectShape.setFillColor(sf::Color::Red);
		// rectShape.setOutlineColor(sf::Color::Red);
		shape.setPosition(position);
		shape.setOrigin(radius, radius);
		//shape.rotate(-90 * deltaTime.count());
		sf::CircleShape pos= sf::CircleShape(1);
		pos.setPosition(position);
		pos.setFillColor(sf::Color::Magenta);
		pos.setOutlineColor(sf::Color::Magenta);
		// rt.draw(rectShape);
		rt.draw(shape);
		// rt.draw(min);
		// rt.draw(max);
		rt.draw(pos);
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

	// void Particle::loadStatic() {
	// 	font.loadFromFile("IBMPlexMono-Regular.ttf");
	// }

	Particle * randomParticle(float minRadius, float maxRadius)
	{
		Particle* p = new Particle(randomVector2<float>(), (int)randomNumber<float>(minRadius, maxRadius));
		((int)p->radius % 2) == 1 ? p->radius++ : p->radius;
		p->velocity = sf::Vector2f(0, 0);
		// p->velocity = randomVector2<float>(0.0f, 5.0f);
		return p;
	}

	
}
