#include "Worker.h"

Worker::Worker() {}

void Worker::Initialise() 
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\worker.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.1, 0.1));
	m_sprite.setPosition(m_position);
}