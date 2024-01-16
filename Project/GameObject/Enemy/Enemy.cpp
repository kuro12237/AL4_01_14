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
	attackTimer_++;

	if (attackTimer_>attackTimerMax_)
	{
		shared_ptr<EnemyBullet>bullet = make_unique<EnemyBullet>();
		bullet->Initialize(worldTransform_.translate,{0.0f,0.0f,-0.1f});
		bullets_.push_back(bullet);
		attackTimer_ = 0;
	}

	for (shared_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection view)
{


   for (shared_ptr<EnemyBullet>& bullet : bullets_) 
   {
	   bullet->Draw(view);
   }

	gameObject_->Draw(worldTransform_, view);
}
