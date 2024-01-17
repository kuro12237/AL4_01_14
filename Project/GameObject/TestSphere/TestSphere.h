#pragma once

#include"Game3dObject.h"

class TestSpere
{
public:
	TestSpere() {};
	~TestSpere() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransfrom_{};
	uint32_t modelHandle_ = 0;
};