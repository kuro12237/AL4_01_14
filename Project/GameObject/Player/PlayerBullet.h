#pragma once
#include"Game3dObject.h"
#include"OBBCollider.h"

class PlayerBullet:public OBBCollider
{
public:
	PlayerBullet() {};
	~PlayerBullet() {};

	void Initialize(uint32_t modelHandle,Vector3 p, Vector3 v);

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransoform_{};
	Vector3 velocity_ = {};

	bool isDesdFlag = false;
};