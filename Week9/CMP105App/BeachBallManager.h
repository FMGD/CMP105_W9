#pragma once
#include "Ball.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

class BeachBallManager
{
private:
	std::vector<Ball> balls_;
	sf::Vector2f spawn_point_;
	sf::Texture texture_;

	sf::Font font_;
	sf::Text num_balls_txt_;

	Input* input;
	int balls_on_screen_;

public:
	BeachBallManager();
	~BeachBallManager();

	void addNewBall();
	void spawn();
	void update(float dt);
	void deathCheck();
	void render(sf::RenderWindow* window);
	bool thereIsDeadBall();
	void setInput(Input* in);
	void handleInput(float dt);

};

