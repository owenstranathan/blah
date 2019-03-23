#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "particle.hpp"
#include "ovector.hpp"
#include "whatever.hpp"

int SCREEN_HEIGHT = 600;
int SCREEN_WIDTH = 800;
std::chrono::duration<double> deltaTime;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Blah!", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    const int NUM_PARTICLES = 1;
    blah::Particle particles[NUM_PARTICLES];
    auto start = std::chrono::system_clock::now();
    auto end = start;

    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i] = blah::randomParticle();
    }
    // run the program as long as the window is open
    while (window.isOpen())
    {
        end = std::chrono::system_clock::now();
        deltaTime = end - start;
        start = end;
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        for (blah::Particle &p : particles)
        {
            p.kinematics();
            p.draw(window);
        }
        window.display();
    }

    return 0;
}