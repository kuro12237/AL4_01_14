#pragma once
#include"Game3dObject.h"

class Enemy
{
public:
	Enemy() {};
	~Enemy() {};

	void Initialize(Vector3 p, uint32_t modelHandle);

	void Update();

	void Draw(ViewProjection view);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};

};