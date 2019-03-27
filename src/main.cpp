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

int SCREEN_HEIGHT = 600;
int SCREEN_WIDTH = 800;
chrono::duration<float> deltaTime;

chrono::time_point<chrono::system_clock> keepTime(chrono::time_point<chrono::system_clock> start) {
	auto end = chrono::system_clock::now();
    deltaTime = end - start;
	return end;
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 10;

    RenderWindow window(VideoMode(800, 600), "Blah!", Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    const int NUM_PARTICLES = 1;
	SAP sap;
	vector<Particle *> particles;

    auto start = chrono::system_clock::now();
    auto end = start;
	auto p = new Particle(sf::Vector2f(100, 100), 20);
	particles.push_back(p); sap.addParticle(p);
	p = new Particle(sf::Vector2f(110, 110), 20);
	particles.push_back(p); sap.addParticle(p);
	p = new Particle(sf::Vector2f(105, 120), 15);
	particles.push_back(p); sap.addParticle(p);
	p = new Particle(sf::Vector2f(200, 200), 15);
	particles.push_back(p); sap.addParticle(p);
  //  for (int i = 0; i < NUM_PARTICLES; i++)
  //  {
		//// auto p = randomParticle();
		//particles.push_back(p);
  //      sap.addParticle(p);
  //  }
	vector<int> test = { 4,15,7,9,0,6,4,2 };
	auto print_vec = [](vector<int> &t) {
		for (auto i : t) {
			cout << i << ",";
		}
		cout << endl;
	};
	print_vec(test);
	insertion_sort<int>(test.begin(), test.end(), [](int a, int b) { return a < b; });
	print_vec(test);
    // run the program as long as the window is open
    while (window.isOpen())
    {
		start = keepTime(start);

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
		sap.resolveCollisions();
    }

    return 0;
}