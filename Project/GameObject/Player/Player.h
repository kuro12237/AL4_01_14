#pragma once

#include"Game3dObject.h"
#include"Input.h"
#include"PlayerBullet.h"
#include"Collider/OBBCollider.h"
#include"CollisionManager.h"
#include"ColliderConfig.h"

class Player :public OBBCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update(const ViewProjection &view);

	void Draw(ViewProjection view);


	list<shared_ptr<PlayerBullet>>GetBullets_(){return bullets_; }

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;

	void SetParent(const WorldTransform* w) { worldTransform_.parent = w; }

private:

	void Control();
	void Attack();

	void ReticleUpdate(const ViewProjection& view);

	uint32_t modelHandle_ = 0;
	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};
	Vector2 velocity_ = {};

	unique_ptr<Game3dObject>gameReticleObject_ = nullptr;
	WorldTransform reticleWorldTransform_ = {};

	uint32_t bulletModelHandle_ = 0;
	list<shared_ptr<PlayerBullet>>bullets_ = {};

};