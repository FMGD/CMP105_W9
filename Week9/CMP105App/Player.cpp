#include "Player.h"

Player::Player()
{

}


Player::~Player()
{
}

void Player::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::W)) //Move Up
	{
		input->setKeyUp(sf::Keyboard::W);
		velocity.y = 8000.f;
		move(0 * dt, -velocity.y * dt);
	}
	else if (input->isKeyDown(sf::Keyboard::S)) //Move Down
	{
		input->setKeyUp(sf::Keyboard::S);
		velocity.y = 8000.f;
		move(0 * dt, velocity.y * dt);
	}

	if (input->isKeyDown(sf::Keyboard::A)) //Move left
	{
		input->setKeyUp(sf::Keyboard::A);
		velocity.x = 8000.f;
		move(-velocity.x * dt, 0 * dt);
	}
	else if (input->isKeyDown(sf::Keyboard::D)) //Move right
	{
		input->setKeyUp(sf::Keyboard::D);
		velocity.x = 8000.f;
		move(velocity.x * dt, 0 * dt);
	}

	if (input->isKeyDown(sf::Keyboard::Enter)) // Shoot
	{
		input->setKeyUp(sf::Keyboard::Enter);
		shoot(getPosition() + sf::Vector2f(getSize().x / 2, getSize().y / 2) );
	}

}

void Player::update(float dt)
{
	// call update on all ALIVE ammunition
	for (int i = 0; i < ammunition_.size(); i++)
	{
		if (ammunition_[i]->isAlive())
		{
			ammunition_[i]->update(dt);
		}
	}

	// Check if some spawnable/ ball has to die
	bulletDeathCheck();
}


void Player::shoot(sf::Vector2f pos)
{
	// Check if there are bullets
	if (!thereAreBullets())
	{
		reloadMagazine();
	}

	// Shoot
	for (int i = 0; i < ammunition_.size(); i++)
	{
		if (!ammunition_[i]->isAlive())
		{
			ammunition_[i]->setAlive(true);
			ammunition_[i]->setPosition(pos);
			return; // Remouve this line this if want to shot all the bullets in one shoot
		}
	}

}


bool Player::thereAreBullets()
{
	for (int i = 0; i < ammunition_.size(); i++)
	{
		if (!ammunition_[i]->isAlive())
		{
			return true;
		}
	}
	return false;
}

void Player::reloadMagazine()
{
	ammunition_.push_back(new Bullet());
	ammunition_.back()->setAlive(false);
}

// Check all ALIVE ammunition to see if outscreen screen/range, if so make dead
void Player::bulletDeathCheck()
{
	for (int i = 0; i < ammunition_.size(); i++)
	{
		if (ammunition_[i]->isAlive())
		{
			if (ammunition_[i]->getPosition().x > window_->getSize().x)
			{
				ammunition_[i]->setAlive(false);
			}
		}

	}

}

std::vector<Bullet*> Player::getAmmunition()
{
	return ammunition_;
}

void Player::setInput(Input* in)
{
	input = in;
}

void Player::setWindow(sf::RenderWindow* window)
{
	window_ = window;
}