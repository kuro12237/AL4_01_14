#pragma once
#include"Game3dObject.h"

class Skydome
{
public:
	Skydome() {};
	~Skydome() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	uint32_t modelHandle_ = 0;

};