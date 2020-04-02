#pragma once
#include "Ball.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

class BeachBallManager2
{
private:
	std::vector<Ball> balls_;
	sf::Texture texture_;

	sf::Font font_;
	sf::Text num_balls_txt_;
	int balls_on_screen_;

	Input* input_;
	sf::RenderWindow* window_;

public:
	BeachBallManager2();
	~BeachBallManager2();

	void addNewBall();
	void spawn();
	void update(float dt);
	void deathCheck();
	void render();
	bool thereIsDeadBall();
	void setInput(Input* in);
	void handleInput(float dt);
	void setWindow(sf::RenderWindow* window);

};
