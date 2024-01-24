#pragma once
#include"Game3dObject.h"
#include"EnemyBullet.h"
#include"OBBCollider.h"
#include"ColliderConfig.h"
#include"state/IEnemyState.h"
#include"state/EnemyApprochState.h"
#include"GameObject/Player/Player.h"
#include"AABBCollider.h"

class Enemy:public AABBCollider
{
public:
	Enemy() {};
	~Enemy() {};

	void Initialize(Vector3 p, uint32_t modelHandle);

	void Update(Player*player);

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;

	bool GetIsDeadFlag() { return isDeadFlag_; }

	Vector3 GetWorldTranslate() { return worldTransform_.translate; }

	void SetWorldTranslate(Vector3 t) { worldTransform_.translate = t; }

	void ChangeState(unique_ptr<IEnemyState> state);

	list<shared_ptr<EnemyBullet>>GetBulletsList() { return bullets_; }

private:

	unique_ptr<Game3dObject>gameObject_ = nullptr;
	WorldTransform worldTransform_ = {};

	list<shared_ptr<EnemyBullet>>bullets_;

	uint32_t attackTimer_ = 0;
	const uint32_t attackTimerMax_ = 20;

	bool isDeadFlag_ = false;

	unique_ptr<IEnemyState>state_ = nullptr;

};