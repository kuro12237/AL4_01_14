#pragma once

#include"Game3dObject.h"

class TestGround
{
public:
	TestGround() {};
	~TestGround() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};


	uint32_t modelhandle_ = 0;
};