#pragma once
#include "Framework/GameObject.h"
class Ball :	public GameObject
{
public:
	Ball();
	~Ball();

	void update(float dt) override;

};

