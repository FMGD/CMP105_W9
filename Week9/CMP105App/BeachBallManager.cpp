#include "BeachBallManager.h"


// Constructor
BeachBallManager::BeachBallManager()
{
	spawn_point_ = sf::Vector2f(350, 250);
	texture_.loadFromFile("gfx/Beach_Ball.png");
	int max_spawnables = 20;
	balls_on_screen_ = 0;

	for (int i = 0; i < max_spawnables; i++)
	{
		addNewBall();
	}

	//Text
	if (!font_.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font \n";
	}
	num_balls_txt_.setFont(font_);
	num_balls_txt_.setString("Balls on Screen: 0");
	num_balls_txt_.setCharacterSize(24);
	num_balls_txt_.setFillColor(sf::Color::Red);
	num_balls_txt_.setStyle(sf::Text::Bold | sf::Text::Underlined);

}

// Destructor
BeachBallManager::~BeachBallManager()
{
}


// Spawn new ball
// Find a dead ball, make alive, move to spawn point, give random velocity
void BeachBallManager::spawn()
{
	// If there are not any dead sprite to use we need to add a ball
	if (!thereIsDeadBall())
	{
		std::cout << "Create One" << std::endl;
		addNewBall();
	}

	for (int i = 0; i < balls_.size(); i++)
	{
		if (!balls_[i].isAlive())
		{
			balls_[i].setAlive(true);
			balls_[i].setVelocity(rand() % 200 - 100, rand() % 200 - 100);
			balls_[i].setPosition(spawn_point_);
			balls_on_screen_++;
			return; // Remouve this line this if want to spawn all the balls at same time
		}
	}
	
}

bool BeachBallManager::thereIsDeadBall()
{
	for (int i = 0; i < balls_.size(); i++)
	{
		if (!balls_[i].isAlive())
		{
			return true;
		}
	}

	return false;
}

void BeachBallManager::addNewBall()
{
	balls_.push_back(Ball());
	balls_.back().setAlive(false);
	balls_.back().setTexture(&texture_);
	balls_.back().setSize(sf::Vector2f(100, 100));
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

	num_balls_txt_.setString("Balls on Screen: " + std::to_string(balls_on_screen_)+ "\nBalls on array: " + std::to_string(balls_.size()) );
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
				balls_on_screen_--;
			}
			if (balls_[i].getPosition().x > 800)
			{
				balls_[i].setAlive(false);
				balls_on_screen_--;
			}

			if (balls_[i].getPosition().y < -100)
			{
				balls_[i].setAlive(false);
				balls_on_screen_--;
			}
			if (balls_[i].getPosition().y > 600)
			{
				balls_[i].setAlive(false);
				balls_on_screen_--;
			}
		}
	}

}

void BeachBallManager::setInput(Input* in)
{
	input = in;
}

void BeachBallManager::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		input->setKeyUp(sf::Keyboard::Space);
		spawn();
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

	window->draw(num_balls_txt_);

}