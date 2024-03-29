#pragma once

#include"Game3dObject.h"
#include"Input.h"
#include"PlayerBullet.h"
#include"Collider/OBBCollider.h"
#include"CollisionManager.h"
#include"ColliderConfig.h"
#include"Sprite/Sprite.h"
#include"AABBCollider.h"

class Player :public AABBCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update(const ViewProjection& view);

	void Draw(ViewProjection view);

	void FrontDraw(ViewProjection view);

	list<shared_ptr<PlayerBullet>>GetBullets_() { return bullets_; }

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;

	void SetParent(const WorldTransform* w) { worldTransform_.parent = w;}
	
	void SetReticleParent(const WorldTransform* w) { reticleWorldTransform_.parent = w; }

	void SetEyeTraget(Vector3 e, Vector3 t) { eye_ = e;  target_ = t; }

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

	Vector2 RJoyPos_{};
	Vector2 SpritePos_ = {640.0f,360.0f};
	unique_ptr<Sprite>sprite_ = nullptr;
	uint32_t reticleTexHandle_ = 0;
	WorldTransform spriteWorldTransform_ = {};

	Vector3 eye_ = {};
	Vector3 target_ = {};

	unique_ptr<Game3dObject>wingObject_ = nullptr;
	WorldTransform wingWorldTransform_ = {};
};