#include <iostream>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "whatever.hpp"
#include "particle.hpp"
#include "ovector.hpp"
#include "sap.hpp"

using namespace std;
using namespace blah;
using namespace sf;

int SCREEN_MULT = 80;
int SCREEN_HEIGHT = 9 * SCREEN_MULT;
int SCREEN_WIDTH = 16 * SCREEN_MULT;
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
    auto blah = VideoMode::getDesktopMode();
    int divisor = gcd(blah.width, blah.height);
    auto ratio = std::make_pair(blah.width / divisor, blah.height / divisor);
    //cout << ratio.first << ", " << ratio.second << endl;
	sf::Text infoText;
	sf::Font font;
	font.loadFromFile("IBMPlexMono-Regular.ttf");
	infoText.setFont(font);
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Blah!", Style::Default, settings);
    //window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(100);
    const int NUM_PARTICLES = 1000;
    SAP sap;
    vector<Particle *> particles;
    auto start = chrono::system_clock::now();
    auto end = start;
    for (int i = 0; i < NUM_PARTICLES; i++) {
        auto p = randomParticle(15, 17);
		p->font = font;
        particles.push_back(p); sap.addParticle(p);
    }
    

    // run the program as long as the window is open
	int frames = 0;
	chrono::duration<float> time(0);
    // float avg = 0.f;
	float fixedTimeStep = 0.02f;
	float timeSinceLastFixedUpdate = 0.0f;

	chrono::duration<float> displayProfile;
    while (window.isOpen())
    {
        start = keepTime(start);
        //++frames;
        //float fps = 1.f / deltaTime.count();
        //avg = ((avg*(frames - 1)) + fps) / frames;
		frames++;
		time += deltaTime;
		stringstream infostream;
	    timeSinceLastFixedUpdate += deltaTime.count();
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::White);
		chrono::duration<float> updateProfile;
		auto updateStart = std::chrono::system_clock::now();
        for (auto p = particles.begin(); p != particles.end(); ++p)
        {
			if (timeSinceLastFixedUpdate >= fixedTimeStep)
				(*p)->kinematics();
            (*p)->draw(window);
        }
		auto updateEnd = std::chrono::system_clock::now();
		updateProfile = updateEnd - updateStart;

		chrono::duration<float> collisionProfile;
		if (timeSinceLastFixedUpdate >= fixedTimeStep) {
			auto collisionStart = std::chrono::system_clock::now();
			sap.resolveCollisions();
			auto collisionEnd = std::chrono::system_clock::now();
			collisionProfile = collisionEnd - collisionStart;
		}

		if (timeSinceLastFixedUpdate >= fixedTimeStep)
			timeSinceLastFixedUpdate = 0.0f;
		auto avg = frames / time.count();
		if (frames > 100) {
			frames = 0;
			time = chrono::duration<float>(0);
		}
        infostream << "FrameRate: " << avg << endl;
		infostream << "Collision: " << collisionProfile.count() << endl;
		infostream << "deltaTime: " << deltaTime.count() << endl;
		infostream << "Update   : " << updateProfile.count() << endl;
		infostream << "Display  : " << displayProfile.count() << endl;
		infoText.setString(infostream.str());
		infoText.setPosition(3, 3);
		infoText.setColor(sf::Color::Magenta);
		window.draw(infoText);
		auto displayStart = std::chrono::system_clock::now();
        window.display();
		auto displayEnd = std::chrono::system_clock::now();
		displayProfile = displayEnd - displayStart;
    }
	for (auto&& p : particles)
		delete p;
    return 0;
}
