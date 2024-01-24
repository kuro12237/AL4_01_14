#pragma once
#include"Game3dObject.h"
#include"GameObject/Player/Player.h"

class EnemyBullet:public OBBCollider
{
public:
	EnemyBullet() {};
	~EnemyBullet() {};

	void Initialize(Vector3 pos, Vector3 v);

	void Update(Player*player);

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	Vector3 velocity_ = {};
};
