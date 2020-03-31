#include "BeachBallManager2.h"


// Constructor
BeachBallManager2::BeachBallManager2()
{

	texture_.loadFromFile("gfx/Beach_Ball.png");
	int default_spawnables = 40;
	balls_on_screen_ = 0;

	for (int i = 0; i < default_spawnables; i++)
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
BeachBallManager2::~BeachBallManager2()
{
}


// Spawn new ball
// Find a dead ball, make alive, move to spawn point, give random velocity
void BeachBallManager2::spawn()
{
	int x = 0 + (rand() % (window_->getSize().x - 99)); // Random between 0 and the size of the window-99
	int y = -100;

	spawn_point_ = sf::Vector2f((float)x, (float)y);
	
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
			balls_[i].setVelocity(0, 100 + (rand() % 200));
			balls_[i].setPosition(spawn_point_);
			balls_on_screen_++;
			return; // Remouve this line this if want to spawn all the balls at same time
		}
	}

}

bool BeachBallManager2::thereIsDeadBall()
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

void BeachBallManager2::addNewBall()
{
	balls_.push_back(Ball());
	balls_.back().setAlive(false);
	balls_.back().setTexture(&texture_);
	balls_.back().setSize(sf::Vector2f(100, 100));
}

void BeachBallManager2::update(float dt)
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
	BeachBallManager2::deathCheck();

	num_balls_txt_.setString("Balls on Screen/Alive: " + std::to_string(balls_on_screen_) + "\nBalls on array: " + std::to_string(balls_.size()));
}


// Check all ALIVE balls to see if outscreen screen/range, if so make dead
void BeachBallManager2::deathCheck()
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
			if (balls_[i].getPosition().x > window_->getSize().x)
			{
				balls_[i].setAlive(false);
				balls_on_screen_--;
			}

			//if (balls_[i].getPosition().y < -100)
			//{
			//	balls_[i].setAlive(false);
			//	balls_on_screen_--;
			//}
			if (balls_[i].getPosition().y > window_->getSize().y)
			{
				balls_[i].setAlive(false);
				balls_on_screen_--;
			}
		}
	}

}

void BeachBallManager2::setInput(Input* in)
{
	input_ = in;
}

void BeachBallManager2::handleInput(float dt)
{
	if (input_->isKeyDown(sf::Keyboard::Space))
	{
		input_->setKeyUp(sf::Keyboard::Space);
		spawn();
	}
}

// Render all ALIVE balls
void BeachBallManager2::render()
{

	for (int i = 0; i < balls_.size(); i++)
	{
		if (balls_[i].isAlive())
		{
			window_->draw(balls_[i]);
		}
	}

	window_->draw(num_balls_txt_);

}

void BeachBallManager2::setWindow(sf::RenderWindow* window)
{
	window_ = window;
}