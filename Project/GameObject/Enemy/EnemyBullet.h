#pragma once
#include"Game3dObject.h"
#include"GameObject/Player/Player.h"
#include"ColliderConfig.h"

class EnemyBullet:public AABBCollider
{
public:
	EnemyBullet() {};
	~EnemyBullet() {};

	void Initialize(Vector3 pos, Vector3 v);

	void Update(Player*player);

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;

	bool GetIsDeadFlag() { return isDeadFlag_; }

private:

	bool isDeadFlag_ = false;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	Vector3 velocity_ = {};
	uint32_t AliveTimer_ = 0;
	uint32_t kAliveTimer_ = 300;
};
