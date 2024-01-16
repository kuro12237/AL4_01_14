#pragma once
#include"Game3dObject.h"
#include"EnemyBullet.h"

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

	list<shared_ptr<EnemyBullet>>bullets_;

	uint32_t attackTimer_ = 0;
	const uint32_t attackTimerMax_ = 180;

};