#include "PlayerBullet.h"

void PlayerBullet::Initialize(uint32_t modelHandle,Vector3 p, Vector3 v)
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle);
	
	worldTransoform_.Initialize();
	worldTransoform_.translate = p;
	worldTransoform_.UpdateMatrix();
	velocity_ = v;
}

void PlayerBullet::Update()
{
	worldTransoform_.translate = VectorTransform::Add(worldTransoform_.translate, velocity_);
	
	worldTransoform_.UpdateMatrix();
}

void PlayerBullet::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransoform_, view);
}
