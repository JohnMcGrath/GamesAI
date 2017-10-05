#include "Player.h"

void Player::HandleInput() {
	if (sf::Event::KeyPressed == event.type) //user key press
	{
		//SF Event in PhysObj.h may cause issues?

		if (sf::Keyboard::Up == event.key.code)
		{
		//	m_velocity.y -= 1;
		}
		if (sf::Keyboard::Down == event.key.code)
		{
		//	rectVelocity.y += 1;
		}
		if (sf::Keyboard::Left == event.key.code)
		{
		//	rectVelocity.x -= 1;
		}
		if (sf::Keyboard::Right == event.key.code)
		{
		//	rectVelocity.x += 1;
		}
	}
}

void Player::Update() {
	this->HandleInput();
	this->setPosition(getPosition() + getVelocity());
}