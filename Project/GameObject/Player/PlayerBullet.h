#pragma once
#include"Game3dObject.h"

class PlayerBullet
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};

	void Initialize(uint32_t modelHandle,Vector3 p, Vector3 v);

	void Update();

	void Draw(ViewProjection view);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransoform_{};
	Vector3 velocity_ = {};
};