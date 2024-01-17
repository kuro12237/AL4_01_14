#pragma once
#include"Game3dObject.h"
#include"GameObject/Player/Player.h"

class EnemyBullet
{
public:
	EnemyBullet() {};
	~EnemyBullet() {};

	void Initialize(Vector3 pos, Vector3 v);

	void Update(Player*player);

	void Draw(ViewProjection view);

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	Vector3 velocity_ = {};
};
