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

	reticleTexHandle_ = TextureManager::LoadTexture("Reticle.png");
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState,{-32.0f,-32.0f});
	sprite_->SetTexHandle(reticleTexHandle_);
	

	spriteWorldTransform_.Initialize();
	spriteWorldTransform_.translate = { 640.0f,360.0f,0.0f };
}

void Player::Update(const ViewProjection& view)
{
	ReticleUpdate(view);
	Control();
	Attack();
	
	spriteWorldTransform_.UpdateMatrix();
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

void Player::FrontDraw(ViewProjection view)
{
	sprite_->Draw(spriteWorldTransform_, view);
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

	//
	RJoyPos_ = Input::GetJoyRStickPos();

	Vector2 RVelocity{ RJoyPos_.x *= 5.0f,RJoyPos_.y *= -5.0f };

	spriteWorldTransform_.translate.x += RVelocity.x;
	spriteWorldTransform_.translate.y += RVelocity.y;


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
		velocity = VectorTransform::TransformNormal(velocity, worldTransform_.matWorld);

		shared_ptr<PlayerBullet>bullet = make_shared<PlayerBullet>();
		bullet->Initialize(bulletModelHandle_,GetWorldPosition(), velocity);
		bullets_.push_back(bullet);
	}
}

void Player::ReticleUpdate(const ViewProjection& view)
{
	
	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = { 0, 0, 1.0f };


	offset = VectorTransform::TransformNormal(offset, worldTransform_.matWorld);
	offset = VectorTransform::Normalize(offset);

	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;


	reticleWorldTransform_.translate = VectorTransform::Add(worldTransform_.translate, offset);


	//座標変換
	Matrix4x4 matViewport =
		MatrixTransform::ViewportMatrix(0.0f, 0.0f, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 1.0f);

	Matrix4x4 matVPV =
		MatrixTransform::Multiply(view.matView_,
			MatrixTransform::Multiply(view.matProjection_, matViewport));

	Matrix4x4 matInverseVPV = MatrixTransform::Inverse(matVPV);

	// スクリーン座標
	Vector3 posNear = Vector3(
		(float)spriteWorldTransform_.translate.x, (float)spriteWorldTransform_.translate.y, 0);
	Vector3 posFar = Vector3(
		(float)spriteWorldTransform_.translate.x, (float)spriteWorldTransform_.translate.y, 1);
	posNear = VectorTransform::TransformByMatrix(posNear, matInverseVPV);
	posFar = VectorTransform::TransformByMatrix(posFar, matInverseVPV);

	Vector3 mouseDirection = VectorTransform::Subtruct(posFar, posNear);
	mouseDirection = VectorTransform::Normalize(mouseDirection);

	const float kDistanceTestObject = 50.0f;

	reticleWorldTransform_.translate.x = posNear.x + mouseDirection.x * kDistanceTestObject;
	reticleWorldTransform_.translate.y = posNear.y + mouseDirection.y * kDistanceTestObject;
	reticleWorldTransform_.translate.z = posNear.z + mouseDirection.z * kDistanceTestObject;
	
	reticleWorldTransform_.translate =
		VectorTransform::Add(posNear,
			VectorTransform::Multiply(
				mouseDirection, { kDistanceTestObject,kDistanceTestObject,kDistanceTestObject })
		);

	reticleWorldTransform_.UpdateMatrix();
}
