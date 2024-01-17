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
	worldTransform_.translate.z += 32.0f;

	reticleWorldTransform_.Initialize();
	gameReticleObject_ = make_unique<Game3dObject>();
	gameReticleObject_->Create();
	gameReticleObject_->SetModel(modelHandle_);
	gameReticleObject_->SetColor({ 1,0,0,1 });
}

void Player::Update()
{
	ReticleUpdate();
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
	gameReticleObject_->Draw(reticleWorldTransform_, view);
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
		
		// BulletSpeed
		const float kBulletSpeed = 1.0f;

		Vector3 reticlePos{};
		reticlePos.x = reticleWorldTransform_.matWorld.m[3][0];
		reticlePos.y = reticleWorldTransform_.matWorld.m[3][1];
		reticlePos.z = reticleWorldTransform_.matWorld.m[3][2];
		velocity = VectorTransform::Subtruct(reticlePos, GetWorldPosition());
		velocity = VectorTransform::Normalize(velocity);

		velocity.x *= kBulletSpeed;
		velocity.y *= kBulletSpeed;
		velocity.z *= kBulletSpeed;

		// intealize
		velocity = VectorTransform::TransformNormal(velocity, worldTransform_.matWorld);

		shared_ptr<PlayerBullet>bullet = make_shared<PlayerBullet>();
		bullet->Initialize(bulletModelHandle_,GetWorldPosition(), velocity);
		bullets_.push_back(bullet);
	}
}

void Player::ReticleUpdate()
{
	
	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = { 0, 0, 1.0f };

	Vector3 pos = GetWorldPosition();

	offset = VectorTransform::TransformNormal(offset, worldTransform_.matWorld);
	offset = VectorTransform::Normalize(offset);

	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;
	reticleWorldTransform_.translate.x = offset.x + pos.x;
	reticleWorldTransform_.translate.y = offset.y + pos.y;
	reticleWorldTransform_.translate.z = offset.z + pos.z;

	Vector2 RJoyPos = Input::GetJoyRStickPos();

	RJoyPos.x *= 5.0f;
	RJoyPos.y *= 5.0f;
	reticleWorldTransform_.translate.x += RJoyPos.x;
	reticleWorldTransform_.translate.y += RJoyPos.y;
	reticleWorldTransform_.UpdateMatrix();
}
