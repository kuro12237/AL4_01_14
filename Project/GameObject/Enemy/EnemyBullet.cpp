#include "EnemyBullet.h"

void EnemyBullet::Initialize(Vector3 pos,Vector3 v)
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();

	uint32_t modelHandle = ModelManager::LoadObjectFile("EnemyBullet");
	gameObject_->SetModel(modelHandle);

	worldTransform_.Initialize();

	worldTransform_.translate = pos;
	worldTransform_.UpdateMatrix();
	velocity_ = v;
}

void EnemyBullet::Update()
{

	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);
}
