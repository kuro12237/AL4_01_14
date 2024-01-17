#pragma once
#include"Light/LightingManager.h"

class RightLight
{
public:
	RightLight() {};
	~RightLight() {};

	void Initialize();

	void Update();


private:

	PointLight_param pointLight_{};

};
