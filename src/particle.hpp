#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace blah
{

template <typename T>
class Particle
{
  public:
    Particle();
    // Particle(const sf::Vector2<double> &);
    ~Particle();

    void draw(sf::RenderTarget &);
    void updateShape();
    void kinematics();
    bool collision(const Particle &);
    void collide(const Particle &);

    sf::Vector2<T> position;
    sf::Vector2<T> velocity;
    sf::Vector2<T> acceleration;
    T radius;
    sf::Color primaryColor;
    sf::Color secondaryColor;
    sf::CircleShape shape;
    T outlineThickness = 1;
    T drawDistance = 200;
    int vertices = 7;
};

template <typename T>
Particle<T>::Particle() : position(sf::Vector2<T>()),
                       velocity(sf::Vector2<T>()),
                       acceleration(sf::Vector2<T>()),
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

template <typename T>
Particle<T>::~Particle()
{
}

template <typename T>
void Particle<T>::draw(sf::RenderTarget &rt)
{
    shape.setPosition(position.x, position.y);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.rotate(-90 * deltaTime.count());
    rt.draw(shape);
}


template <typename T>
bool Particle<T>::collision(const Particle &p)
{
    sf::Vector3<T> relativePosition = position - p.position;
    double distanceSquared = squareMagnitude(relativePosition);
    double squareCollisionRadius = std::pow((radius + p.radius), 2);
    return distanceSquared < squareCollisionRadius;
}

template <typename T>
void Particle<T>::collide(const Particle &p)
{
    sf::Vector2<T> relativePosition = position - p.position;
    sf::Vector2<T> relativeCollisionPoint = normalized(relativePosition) * radius;
    sf::Vector2<T> collisionPoint = position + relativeCollisionPoint;
    sf::Vector2<T> correctiveForce = normalized(collisionPoint - p.position) * p.radius;
    velocity += correctiveForce;
}

template <typename T>
void Particle<T>::kinematics()
{
    position += velocity;
    velocity += acceleration;
    acceleration = sf::Vector2<T>();

    double diff = position.x - radius;
    if (diff < 0)
    {
        Particle<T> fakey = Particle<T>();
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
            Particle<T> fakey = Particle<T>();
            fakey.position.x = diff;
            fakey.position.y = position.y;
            fakey.radius = std::abs(diff - SCREEN_WIDTH);
            collide(fakey);
        }
    }
    diff = position.y - radius;
    if (diff < 0)
    {
        Particle<T> fakey = Particle<T>();
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
            Particle<T> fakey = Particle<T>();
            fakey.position.x = position.x;
            fakey.position.y = diff;
            fakey.radius = std::abs(diff - SCREEN_HEIGHT);
            collide(fakey);
        }
    }
}

template <typename T>
Particle<T> randomParticle()
{
    Particle<T> p = Particle<T>();
    p.radius = randomNumber<T>(1, 30);
    p.position = randomVector2<T>();
    p.velocity = randomVector2<T>(0, 5);
    return p;
}

} // namespace blah

template <typename T>
std::ostream &operator<<(std::ostream &os, blah::Particle<T> &p)
{
    os << "Pos: " << p.position << std::endl
       << "Vel: " << p.velocity << std::endl
       << "Radius: " << p.radius << std::endl;
    return os;
}

