#include "PlayerBullet.h"

void PlayerBullet::Initialize(uint32_t modelHandle,Vector3 p, Vector3 v)
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle);

	worldTransoform_.Initialize();
	worldTransoform_.translate = p;
	worldTransoform_.UpdateMatrix();

	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);

	velocity_ = v;
	float velocityXZ = sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	float heightY = -velocity_.y;

	worldTransoform_.rotation.y = std::atan2(velocity_.x, velocity_.z);
	worldTransoform_.rotation.x = std::atan2(heightY, velocityXZ);

}

void PlayerBullet::Update()
{
	bulletTimer_ ++;

	if (bulletTimer_>=kBulletTimer_)
	{
		isDesdFlag = true;
	}

	worldTransoform_.translate = VectorTransform::Add(worldTransoform_.translate, velocity_);
	worldTransoform_.UpdateMatrix();
}

void PlayerBullet::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransoform_, view);
}

Vector3 PlayerBullet::GetWorldPosition()
{
	return Vector3(
	worldTransoform_.matWorld.m[3][0],
	worldTransoform_.matWorld.m[3][1],
	worldTransoform_.matWorld.m[3][2]
	);
}

void PlayerBullet::OnCollision(uint32_t id)
{
	id;
	isDesdFlag = true;
}
