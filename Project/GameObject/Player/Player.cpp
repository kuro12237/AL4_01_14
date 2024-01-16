#include "Player.h"


void Player::Initialize()
{
	modelHandle_ = ModelManager::LoadObjectFile("Player");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();

}

void Player::Update()
{

	Control();

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);
}

void Player::Control()
{
	Vector2 joyVector = Input::GetJoyLStickPos();

	if (joyVector.x <= 0.1f && joyVector.x >= -0.1f)
	{
		joyVector.x = 0.0f;
	}

	if (joyVector.y <= 0.1f && joyVector.y >= -0.1f)
	{
		joyVector.y = 0.0f;
	}

	velocity_.x = joyVector.x * 0.1f;
	velocity_.y = joyVector.y * 0.1f;

	worldTransform_.translate.x += velocity_.x;
	worldTransform_.translate.y += velocity_.y;
}
