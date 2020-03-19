#include "Ball.h"

Ball::Ball()
{

}

Ball::~Ball()
{

}

void Ball::update(float dt)
{
	move(velocity * dt);
}