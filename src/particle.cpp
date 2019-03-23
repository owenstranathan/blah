
#include <iostream>
#include <SFML/Graphics.hpp>

#include "particle.hpp"
#include "ovector.hpp"
#include "whatever.hpp"

namespace blah
{

Particle::Particle() : position(sf::Vector3<double>()),
                       velocity(sf::Vector3<double>()),
                       acceleration(sf::Vector3<double>()),
                       radius(0),
                       primaryColor(sf::Color::White),
                       secondaryColor(sf::Color::Black)
{
    shape = sf::CircleShape(radius, vertices);
    shape.setFillColor(primaryColor);
    shape.setOutlineThickness(outlineThickness);
    shape.setOutlineColor(secondaryColor);
    shape.setOrigin(radius, radius);
}

Particle::~Particle()
{
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
    sf::Vector3<double> relativePosition = position - p.position;
    double distanceSquared = squareMagnitude(relativePosition);
    double squareCollisionRadius = std::pow((radius + p.radius), 2);
    return distanceSquared < squareCollisionRadius;
}

void Particle::collide(const Particle &p)
{
    sf::Vector3<double> relativePosition = position - p.position;
    sf::Vector3<double> relativeCollisionPoint = normalized(relativePosition) * radius;
    sf::Vector3<double> collisionPoint = position + relativeCollisionPoint;
    sf::Vector3<double> correctiveForce = normalized(collisionPoint - p.position) * p.radius;
    velocity += correctiveForce;
}

void Particle::kinematics()
{
    position += velocity;
    velocity += acceleration;
    acceleration = sf::Vector3<double>();

    double diff = position.x - radius;
    if (diff < 0)
    {
        Particle fakey = Particle();
        fakey.position.x = diff;
        fakey.position.y = position.y;
        fakey.radius = radius;
        collide(fakey);
    }
    else
    {
        diff = position.x + radius;
        if (diff > SCREEN_WIDTH)
        {
            Particle fakey = Particle();
            fakey.position.x = diff;
            fakey.position.y = position.y;
            fakey.radius = std::abs(diff - SCREEN_WIDTH);
            collide(fakey);
        }
    }
    diff = position.y - radius;
    if (diff < 0)
    {
        Particle fakey = Particle();
        fakey.position.x = position.x;
        fakey.position.y = diff;
        fakey.radius = std::abs(diff);
        collide(fakey);
    }
    else
    {
        diff = position.y + radius;
        if (diff > SCREEN_HEIGHT)
        {
            Particle fakey = Particle();
            fakey.position.x = position.x;
            fakey.position.y = diff;
            fakey.radius = std::abs(diff - SCREEN_HEIGHT);
            collide(fakey);
        }
    }
}

Particle randomParticle()
{
    Particle p = Particle();
    p.radius = randomNumber<double>(1, 30);
    p.position = randomVector3<double>();
    p.velocity = randomVector3<double>(0, 5);
    return p;
}

} // namespace blah

std::ostream &operator<<(std::ostream &os, blah::Particle &p)
{
    os << "Pos: " << p.position << std::endl
       << "Vel: " << p.velocity << std::endl
       << "Radius: " << p.radius << std::endl;
    return os;
}
