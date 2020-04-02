#include "PlayerManager.h"

// Constructor
PlayerManager::PlayerManager()
{
	spawn_point_ = sf::Vector2f(0, 350);
	texture_.loadFromFile("gfx/Goomba.png");

	player_.setTexture(&texture_);
	player_.setSize(sf::Vector2f(15 * 2, 21 * 2));
	player_.setPosition(spawn_point_);

}

// Destructor
PlayerManager::~PlayerManager()
{
}

// Functions
void PlayerManager::update(float dt)
{
	player_.update(dt);
}

void PlayerManager::render(sf::RenderWindow* window)
{
	std::vector<Bullet*> ammunition_ = player_.getAmmunition();

	window->draw(player_);

	for (int i = 0; i < ammunition_.size(); i++)
	{
		if (ammunition_[i]->isAlive())
		{
			window->draw(*ammunition_[i]);
		}
	}
}

void PlayerManager::handleInput(float dt)
{
	player_.handleInput(dt);
}

void PlayerManager::setInput(Input* in)
{
	player_.setInput(in);
}

void PlayerManager::setWindow(sf::RenderWindow* window)
{
	player_.setWindow(window);
	window_ = window;
}


