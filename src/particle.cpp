#include "particle.hpp"
#include "whatever.hpp"
#include "ovector.hpp"
#include "aabb.hpp"


namespace blah {
	Particle::Particle() : position(sf::Vector2<float>()),
		velocity(sf::Vector2<float>()),
		acceleration(sf::Vector2<float>()),
		radius(0),
		primaryColor(sf::Color::White),
		secondaryColor(sf::Color::Black)
	{
		aabb = new AxisAlignedBoundingBox(this);
		shape = sf::CircleShape(radius, vertices);
		shape.setFillColor(primaryColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(secondaryColor);
		shape.setOrigin(radius, radius);
	}

	Particle::~Particle()
	{
		delete aabb;
	}

	void Particle::draw(sf::RenderTarget &rt)
	{
		shape.setPosition(position.x, position.y);
		shape.setRadius(radius);
		shape.setOrigin(radius, radius);
		shape.rotate(-90 * deltaTime.count());
		rt.draw(shape);
	}


	bool Particle::collision(const Particle &p)
	{
		sf::Vector2<float> relativePosition = position - p.position;
		double distanceSquared = squareMagnitude(relativePosition);
		double squareCollisionRadius = std::pow((radius + p.radius), 2);
		return distanceSquared < squareCollisionRadius;
	}

	void Particle::collide(const Particle &p)
	{
		sf::Vector2<float> relativePosition = position - p.position;
		sf::Vector2<float> relativeCollisionPoint = normalized(relativePosition) * radius;
		sf::Vector2<float> collisionPoint = position + relativeCollisionPoint;
		sf::Vector2<float> correctiveForce = normalized(collisionPoint - p.position) * p.radius;
		velocity += correctiveForce;
	}

	void Particle::kinematics()
	{
		position += velocity;
		velocity += acceleration;
		acceleration = sf::Vector2<float>();
 
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


	Particle * randomParticle()
	{
		Particle* p = new Particle();
		p->radius = randomNumber<float>(1, 30);
		p->position = randomVector2<float>();
		p->velocity = randomVector2<float>(0, 5);
		return p;
	}
}