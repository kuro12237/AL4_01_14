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
	SetCollisionMask(kCollisionMaskEnemy);
	SetCollosionAttribute(kCollisionAttributeEnemy);
	//velocity_ = VectorTransform::Multiply(velocity_, { 10.0f,10.0f,10.0f });
}

void EnemyBullet::Update(Player*player)
{
	AliveTimer_++;
	if (AliveTimer_>=kAliveTimer_)
	{
		isDeadFlag_ = true;
	}

	Vector3 PlayerPos = {};
	PlayerPos = VectorTransform::Subtruct(player->GetWorldPosition(), worldTransform_.translate);

	Vector3 NomalisePlayer = VectorTransform::Normalize(PlayerPos);
	Vector3 NomalizeVelocity = VectorTransform::Normalize(velocity_);

	velocity_ = VectorTransform::SlerpFanc(NomalizeVelocity, NomalisePlayer, 0.05f);

	//向き
	float velocityXZ = sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	float heightY = -velocity_.y;

	worldTransform_.rotation.y = std::atan2(velocity_.x, velocity_.z);
	worldTransform_.rotation.x = std::atan2(heightY, velocityXZ);

	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, velocity_);
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);
}

Vector3 EnemyBullet::GetWorldPosition()
{
	return Vector3(
		worldTransform_.matWorld.m[3][0],
		worldTransform_.matWorld.m[3][1],
		worldTransform_.matWorld.m[3][2]
	);
}

void EnemyBullet::OnCollision(uint32_t id)
{
	id;
	isDeadFlag_ = true;
}
