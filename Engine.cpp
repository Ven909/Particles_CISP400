#include "Engine.h"

Engine::Engine()
{
	//set size of window with respect to the computer width and height and make the window
	m_Window.create(VideoMode::getDesktopMode(), "Particles", Style::Default);
	srand(time(0)); //may not need this
}


void Engine::run()
{
	Clock clock; //Construct a local Clock object to track time per frame

	//unit tests
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	//while m_Window is open...
	while (m_Window.isOpen())
	{
		Time dt = clock.restart(); //restart clock

		float dtAsSeconds = dt.asSeconds(); //convert to seconds
		input();             //handle user input
		update(dtAsSeconds); // Call update to update the game state using elapsed time
		draw();             // draw everything to render game
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		// exit game using x button or esc key
		if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
		{		
			// Create a loop to construct 5 particles
			for (int i = 0; i < 5; i++)
			{
				//srand(time(0));  //may wanna exclude this
				int numPoints = rand() % (50 - 25 + 1) + 25;        //rand() % 26 + 25;  // range is [25:50] 

				//Pass the position of the mouse click into the constructor
				Particle particle(m_Window, numPoints, Mouse::getPosition());
        		m_particles.push_back(particle);  //push each particle into vector
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	// Loop thru m_particles and update each one using an iterATOR BASED FOR LOOP
	for (auto i = m_particles.begin(); i != m_particles.end();)
	{
		// Call update on each particle if ttl has not expired
		if (i->getTTL() > 0.0)
		{
			i->update(dtAsSeconds); //update position
			i++;                    // increment
		}
        // else, particle's ttl has expired so, erase from vector
		else
		{
			i = m_particles.erase(i);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	//Loop through each Particle in m_Particles and draw
	for (Particle parti : m_particles)
	{
		m_Window.draw(parti);
	}
	/*
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles[i]);
	}
	*/
	m_Window.display(); //display everything created

}
