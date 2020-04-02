#pragma once

#include "Framework/GameObject.h"
#include "Bullet.h"
#include <vector>

class Player : public GameObject
{
public:
	Player();
	~Player();

	void update(float dt) override;
	void handleInput(float dt) override;
	void setInput(Input* in);
	void setWindow(sf::RenderWindow* window);

	bool thereAreBullets();
	void reloadMagazine();
	void shoot(sf::Vector2f pos);
	void bulletDeathCheck();
	std::vector<Bullet*> getAmmunition();	

private:
	std::vector<Bullet*> ammunition_;
	sf::RenderWindow* window_;
};