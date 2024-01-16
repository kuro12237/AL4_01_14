#pragma once

#include"Game3dObject.h"
#include"Input.h"
#include"PlayerBullet.h"

class Player
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

private:

	void Control();
	void Attack();


	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	Vector2 velocity_ = {};

	uint32_t bulletModelHandle_ = 0;
	list<shared_ptr<PlayerBullet>>bullets_ = {};

};