#include "BeachBallManager.h"

// Constructor
BeachBallManager::BeachBallManager()
{
	spawn_point_ = sf::Vector2f(350, 250);
	texture_.loadFromFile("gfx/Beach_Ball.png");
	int max_spawnables = 20;

	for (int i = 0; i < max_spawnables; i++)
	{
		balls_.push_back(Ball());
		balls_[i].setAlive(false);
		balls_[i].setTexture(&texture_);
		balls_[i].setSize(sf::Vector2f(100, 100));
	}

}

// Destructor
BeachBallManager::~BeachBallManager()
{
}

// Spawn new ball
// Find a dead ball, make alive, move to spawn point, give random velocity
void BeachBallManager::spawn()
{
	for (int i = 0; i < balls_.size(); i++)
	{
		if (!balls_[i].isAlive())
		{
			balls_[i].setAlive(true);
			balls_[i].setVelocity(rand() % 200 - 100, rand() % 200 - 100);
			balls_[i].setPosition(spawn_point_);
			return;
		}
	}
}

void BeachBallManager::update(float dt)
{
	// call update on all ALIVE balls
	for (int i = 0; i < balls_.size(); i++)
	{
		if (balls_[i].isAlive())
		{
			balls_[i].update(dt);
		}
	}

	// Check if some spawnable/ ball has to die
	BeachBallManager::deathCheck();
}


// Check all ALIVE balls to see if outscreen screen/range, if so make dead
void BeachBallManager::deathCheck()
{
	for (int i = 0; i < balls_.size(); i++)
	{
		if (balls_[i].isAlive())
		{
			if (balls_[i].getPosition().x < -100)
			{
				balls_[i].setAlive(false);
			}
			if (balls_[i].getPosition().x > 800)
			{
				balls_[i].setAlive(false);
			}

			if (balls_[i].getPosition().y < -100)
			{
				balls_[i].setAlive(false);
			}
			if (balls_[i].getPosition().y > 600)
			{
				balls_[i].setAlive(false);
			}
		}
	}

}

// Render all ALIVE balls
void BeachBallManager::render(sf::RenderWindow* window)
{

	for (int i = 0; i < balls_.size(); i++)
	{
		if (balls_[i].isAlive())
		{
			window->draw(balls_[i]);
		}
	}

}