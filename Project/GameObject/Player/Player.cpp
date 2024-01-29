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

	reticleTexHandle_ = TextureManager::LoadPngTexture("Reticle.png");
	sprite_ = make_unique<Sprite>();
	sprite_->Initialize(new SpriteBoxState,{-32.0f,-32.0f});
	sprite_->SetTexHandle(reticleTexHandle_);

	//reticleWorldTransform_.parent = &worldTransform_;
	reticleWorldTransform_.translate.z += 10.0f;
	spriteWorldTransform_.Initialize();
	spriteWorldTransform_.translate = { 640.0f,360.0f,0.0f };
	uint32_t wingModelHandle = ModelManager::LoadObjectFile("PlayerWing");
	wingObject_ = make_unique<Game3dObject>();
	wingObject_->Create();
	wingObject_->SetModel(wingModelHandle);
	wingWorldTransform_.Initialize();
	wingWorldTransform_.parent = &worldTransform_;
	wingWorldTransform_.scale = { 5,5,5 };
}

void Player::Update(const ViewProjection& view)
{
	gameObject_->SetColor({ 1,1,1,1 });
	Control();
	Attack();
	ReticleUpdate(view);
	wingWorldTransform_.rotation.y += 0.05f;

	for (shared_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();

	}

	spriteWorldTransform_.UpdateMatrix();
	worldTransform_.UpdateMatrix();
	wingWorldTransform_.UpdateMatrix();
	bullets_.remove_if([](shared_ptr<PlayerBullet> bullet) {
		if (bullet->GetIsDadFlag()) {
			bullet.reset();
			return true;
		}
		return false;
		});
}

void Player::Draw(ViewProjection view)
{
	for (shared_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(view);

	}
	wingObject_->Draw(wingWorldTransform_, view);
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
	gameObject_->SetColor({ 1,0,0,1 });
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
	reticleWorldTransform_.UpdateMatrix();
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
		velocity = VectorTransform::TransformNormal(velocity,reticleWorldTransform_.matWorld);

		shared_ptr<PlayerBullet>bullet = make_shared<PlayerBullet>();
		bullet->Initialize(bulletModelHandle_,GetWorldPosition(), velocity);
		bullets_.push_back(bullet);
	}
}

void Player::ReticleUpdate(const ViewProjection& view)
{
	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = { 0, 0, 1.0f };

	Vector3 pos;
	pos.x = worldTransform_.matWorld.m[3][0];
	pos.y = worldTransform_.matWorld.m[3][1];
	pos.z = worldTransform_.matWorld.m[3][2];

	offset = VectorTransform::TransformNormal(offset, worldTransform_.matWorld);
	offset = VectorTransform::Normalize(offset);

	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;
	reticleWorldTransform_.translate.x = offset.x + pos.x;
	reticleWorldTransform_.translate.y = offset.y + pos.y;
	reticleWorldTransform_.translate.z = offset.z + pos.z;
	reticleWorldTransform_.UpdateMatrix();
	
	//コントロール
	RJoyPos_ = Input::GetJoyRStickPos();
	Vector2 RVelocity{ RJoyPos_.x ,RJoyPos_.y };
	SpritePos_.x = SpritePos_.x + RVelocity.x*10;
	SpritePos_.y = SpritePos_.y - RVelocity.y*10;

	spriteWorldTransform_.translate.x = SpritePos_.x;
	spriteWorldTransform_.translate.y = SpritePos_.y;
	spriteWorldTransform_.UpdateMatrix();

	//座標変換
	Matrix4x4 matViewport =
		MatrixTransform::ViewportMatrix(0.0f, 0.0f, float(WinApp::GetkCilientWidth()), float(WinApp::GetkCilientHeight()), 0.0f, 1.0f);

	Matrix4x4 matVPV =
		MatrixTransform::Multiply(view.matView_,
			MatrixTransform::Multiply(view.matProjection_, matViewport));
	Matrix4x4 matInverseVPV = MatrixTransform::Inverse(matVPV);

	// スクリーン座標
	Vector3 posNear = Vector3(
		SpritePos_.x, SpritePos_.y, 0);
	Vector3 posFar = Vector3(
		SpritePos_.x, SpritePos_.y, 1);

	posNear = VectorTransform::TransformByMatrix(posNear, matInverseVPV);
	posFar = VectorTransform::TransformByMatrix(posFar, matInverseVPV);

	Vector3 mouseDirection = VectorTransform::Subtruct(posFar, posNear);
	mouseDirection = VectorTransform::Normalize(mouseDirection);
	const float kDistanceTestObject = -50.0f;

	reticleWorldTransform_.translate.x = posNear.x - mouseDirection.x *kDistanceTestObject;
	reticleWorldTransform_.translate.y = posNear.y - mouseDirection.y *kDistanceTestObject;
	reticleWorldTransform_.translate.z = posNear.z - mouseDirection.z *kDistanceTestObject;
	reticleWorldTransform_.UpdateMatrix();
	reticleWorldTransform_.TransfarMatrix();
}


