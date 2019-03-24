#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "particle.hpp"
#include "ovector.hpp"
#include "whatever.hpp"

using namespace std;
using namespace blah;
using namespace sf;

int SCREEN_HEIGHT = 600;
int SCREEN_WIDTH = 800;
chrono::duration<float> deltaTime;

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 10;

    RenderWindow window(VideoMode(800, 600), "Blah!", Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    const int NUM_PARTICLES = 1;
    Particle* particles[NUM_PARTICLES];
    auto start = chrono::system_clock::now();
    auto end = start;

    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i] = randomParticle();
    }
    // run the program as long as the window is open
    while (window.isOpen())
    {
        end = chrono::system_clock::now();
        deltaTime = end - start;
        start = end;
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::White);
        for (Particle *p : particles)
        {
            p->kinematics();
            p->draw(window);
        }
        window.display();
    }

    return 0;
}