#include "particle.hpp"
#include "whatever.hpp"
#include "ovector.hpp"
#include "aabb.hpp"

namespace blah {
	Particle::Particle() : position(sf::Vector2f()),
		velocity(sf::Vector2f()),
		acceleration(sf::Vector2f()),
		origin(sf::Vector2f()),
		primaryColor(sf::Color::White),
		secondaryColor(sf::Color::Black)
	{
		aabb = new AABB(this);
		shape = sf::CircleShape(radius, vertices);
		origin = sf::Vector2f(radius, radius);
		updateShape();
	}
		
	Particle::Particle(sf::Vector2f & p, float r) : position(p),
		radius(r),
		primaryColor(sf::Color::White),
		secondaryColor(sf::Color::Black) {
		aabb = new AABB(this);
		shape = sf::CircleShape(radius, vertices);
		origin = sf::Vector2f(radius, radius);
		updateShape();
	}

	Particle::~Particle()
	{
		delete aabb;
	}

	void Particle::updateShape() {
		shape.setFillColor(primaryColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(secondaryColor);
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.setPosition(position);
	}
	void Particle::draw(sf::RenderTarget &rt)
	{
		updateShape();
		shape.rotate(-90 * deltaTime.count());
		rt.draw(shape);
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
		sf::Vector2f correctiveForce = normalized(collisionPoint - p.position) * p.radius;
		velocity += correctiveForce;
	}

	void Particle::kinematics()
	{
		if (velocity.x > 3.0f)
			velocity.x = 3.0f;
		if (velocity.y > 3.0f)
			velocity.y = 3.0f;
		
		position += velocity;
		velocity += acceleration;
		acceleration = sf::Vector2f();
 
		if (aabb->min().x < 0)
		{
			Particle fakey = Particle();
			fakey.position.x = aabb->min().x;
			fakey.position.y = position.y;
			fakey.radius = std::abs(aabb->min().x);
			collide(fakey);
		}
		else if (aabb->max().x > SCREEN_WIDTH)
		{
			Particle fakey = Particle();
			fakey.position.x = aabb->max().x;
			fakey.position.y = position.y;
			fakey.radius = std::abs(aabb->max().x - SCREEN_WIDTH);
			collide(fakey);
		}
		if (aabb->min().y < 0)
		{
			Particle fakey = Particle();
			fakey.position.x = position.x;
			fakey.position.y = aabb->min().y;
			fakey.radius = std::abs(aabb->min().y);
			collide(fakey);
		}
		else if (aabb->max().y > SCREEN_HEIGHT)
		{
			Particle fakey = Particle();
			fakey.position.x = position.x;
			fakey.position.y = aabb->max().y;
			fakey.radius = std::abs(aabb->max().y - SCREEN_HEIGHT);
			collide(fakey);
		}
	}

	void Particle::resolveCollision(Particle& a, Particle& b) {
		if (a.collision(b)) {
			a.collide(b);
			b.collide(a);
		}
	}


	Particle * randomParticle()
	{
		Particle* p = new Particle();
		p->radius = randomNumber<float>(1, 30);
		p->position = randomVector2<float>();
		p->velocity = randomVector2<float>(0.0f, 5.0f);
		return p;
	}

	}