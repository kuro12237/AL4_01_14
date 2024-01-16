#include "Enemy.h"

void Enemy::Initialize(Vector3 p,uint32_t modelHandle)
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle);

	worldTransform_.Initialize();
	worldTransform_.translate = p;
	worldTransform_.UpdateMatrix();
}

void Enemy::Update()
{
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);
}
