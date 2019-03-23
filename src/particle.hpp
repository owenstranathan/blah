#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace blah
{

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

    sf::Vector3<double> position;
    sf::Vector3<double> velocity;
    sf::Vector3<double> acceleration;
    double radius;
    sf::Color primaryColor;
    sf::Color secondaryColor;
    sf::CircleShape shape;
    double outlineThickness = 1;
    double drawDistance = 200;
    int vertices = 7;
};

Particle randomParticle();

} // namespace blah

std::ostream &operator<<(std::ostream &, blah::Particle &);
