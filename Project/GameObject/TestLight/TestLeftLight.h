#pragma once
#include"Light/LightingManager.h"

class LeftLight
{
public:
	LeftLight() {};
	~LeftLight() {};

	void Initialize();

	void Update();


private:

	PointLight_param pointLight_{};

};

