#pragma once
#include "Ball.h"
#include <math.h>
#include <vector>

class BeachBallManager
{
private:
	std::vector<Ball> balls_;
	sf::Vector2f spawn_point_;
	sf::Texture texture_;

public:
	BeachBallManager();
	~BeachBallManager();

	void spawn();
	void update(float dt);
	void deathCheck();
	void render(sf::RenderWindow* window);

};

