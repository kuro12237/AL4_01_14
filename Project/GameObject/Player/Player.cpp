#include "Player.h"


void Player::Initialize()
{
	modelHandle_ = ModelManager::LoadObjectFile("Player");
	bulletModelHandle_ = ModelManager::LoadObjectFile("PlayerBullet");

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();
	SetCollosionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);
}

void Player::Update()
{
	Control();
	Attack();

	worldTransform_.UpdateMatrix();
	
	for (shared_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();

	}
}

void Player::Draw(ViewProjection view)
{
	for (shared_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(view);

	}
	gameObject_->Draw(worldTransform_, view);
}

Vector3 Player::GetWorldPosition()
{
	return Vector3(
	worldTransform_.matWorld.m[3][0],
	worldTransform_.matWorld.m[3][1],
	worldTransform_.matWorld.m[3][2]
	);
}

void Player::OnCollision(uint32_t id)
{
	id;

}

void Player::Control()
{
	Vector2 joyLeftVector = Input::GetJoyLStickPos();
	Vector2 joyRightVector = Input::GetJoyRStickPos();

	//LimitR
	if (joyRightVector.x <= 0.1f && joyRightVector.x >= -0.1f)
	{
		joyRightVector.x = 0.0f;
	}
	if (joyRightVector.y <= 0.1f && joyRightVector.y >= -0.1f)
	{
		joyRightVector.y = 0.0f;
	}

	//LimitL
	if (joyLeftVector.x <= 0.1f && joyLeftVector.x >= -0.1f)
	{
		joyLeftVector.x = 0.0f;
	}
	if (joyLeftVector.y <= 0.1f && joyLeftVector.y >= -0.1f)
	{
		joyLeftVector.y = 0.0f;
	}


	velocity_.x = joyLeftVector.x * 0.1f;
	velocity_.y = joyLeftVector.y * 0.1f;

	worldTransform_.translate.x += velocity_.x;
	worldTransform_.translate.y += velocity_.y;
}

void Player::Attack()
{
	if (Input::PushRShoulderPressed())
	{
		const float kbulletSpeed = 1.0f;
		Vector3 velocity = { 0,0,kbulletSpeed };
		velocity = VectorTransform::TransformNormal(velocity, worldTransform_.matWorld);

		shared_ptr<PlayerBullet>bullet = make_shared<PlayerBullet>();
		bullet->Initialize(bulletModelHandle_,worldTransform_.translate, velocity);
		bullets_.push_back(bullet);
	}
}
