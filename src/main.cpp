#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "whatever.hpp"
#include "particle.hpp"
#include "ovector.hpp"
#include "sap.hpp"

using namespace std;
using namespace blah;
using namespace sf;

int SCREEN_HEIGHT = 720;
int SCREEN_WIDTH = 1280;
chrono::duration<float> deltaTime;

chrono::time_point<chrono::system_clock> keepTime(chrono::time_point<chrono::system_clock> start) {
	auto end = chrono::system_clock::now();
    deltaTime = end - start;
	return end;
}

int gcd(int a, int b) {
	return (b == 0) ? a : gcd(b, a % b);
}
	
int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 10;
	Particle::loadStatic();
	auto blah = VideoMode::getDesktopMode();
	int divisor = gcd(blah.width, blah.height);
	auto ratio = std::make_pair(blah.width / divisor, blah.height / divisor);
	cout << ratio.first << ", " << ratio.second << endl;
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Blah!", Style::Default, settings);
    window.setVerticalSyncEnabled(true);
	const int NUM_PARTICLES = 20;
	SAP sap;
	vector<Particle *> particles;
    auto start = chrono::system_clock::now();
    auto end = start;
	for (int i = 0; i < NUM_PARTICLES; i++) {
		auto p = randomParticle();
		particles.push_back(p); sap.addParticle(p);
	}
	/*auto p1 = new Particle(sf::Vector2f(50, 50), 10);
	particles.push_back(p1); sap.addParticle(p1);
	auto p2 = new Particle(sf::Vector2f(SCREEN_WIDTH-50, SCREEN_HEIGHT-50), 10);
	particles.push_back(p2); sap.addParticle(p2);
	auto relpos = p1->position - p2->position;
	p2->velocity = normalized(relpos);
	p1->velocity = -normalized(relpos)*/;
	/*p = new Particle(sf::Vector2f(105, 120), 15);
	particles.push_back(p); sap.addParticle(p);
	p = new Particle(sf::Vector2f(200, 200), 15);
	particles.push_back(p); sap.addParticle(p); */

   // run the program as long as the window is open
	int frames = 0;
	float avg = 0.f;
    while (window.isOpen())
    {
		start = keepTime(start);
		++frames;
		float fps = 1.f / deltaTime.count();
		avg = ((avg*(frames - 1)) + fps) / frames;
		cout << avg << endl;

        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::White);
		for (auto p = particles.begin(); p != particles.end(); ++p)
        {
			(*p)->kinematics();
            (*p)->draw(window);
        }
		sap.resolveCollisions();
        window.display();
    }

    return 0;
}