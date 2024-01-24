#pragma once
#include"Game3dObject.h"
#include"OBBCollider.h"
#include"ColliderConfig.h"
#include"AABBCollider.h"
class PlayerBullet:public AABBCollider
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};

	void Initialize(uint32_t modelHandle,Vector3 p, Vector3 v);

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;
	bool GetIsDadFlag() { return isDesdFlag; }
private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransoform_{};
	Vector3 velocity_ = {};

	uint32_t bulletTimer_ = 0;
	uint32_t kBulletTimer_ = 300;

	bool isDesdFlag = false;
};