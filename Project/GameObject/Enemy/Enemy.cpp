#include "Enemy.h"

void Enemy::Initialize(Vector3 p,uint32_t modelHandle)
{
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle);

	worldTransform_.Initialize();
	worldTransform_.translate = p;
	worldTransform_.UpdateMatrix();
	
	state_ = make_unique<EnemeyApprochState>();

	SetCollosionAttribute(kCollisionAttributeEnemy);
	SetCollisionMask(kCollisionMaskEnemy);
}

void Enemy::Update(Player* player)
{
	bullets_.remove_if([](shared_ptr<EnemyBullet> bullet) {
		if (bullet->GetIsDeadFlag()) {
			bullet.reset();
			return true;
		}
		return false;
		});
	attackTimer_++;

	if (attackTimer_>attackTimerMax_)
	{
		//ベクトル算出
		Vector3 peLarp = VectorTransform::Subtruct(worldTransform_.translate, player->GetWorldPosition());
		Vector3 velocity = VectorTransform::Normalize(peLarp);
		velocity = VectorTransform::TransformNormal(velocity, worldTransform_.matWorld);


		shared_ptr<EnemyBullet>bullet = make_unique<EnemyBullet>();
		bullet->Initialize(worldTransform_.translate,velocity);
		bullets_.push_back(bullet);
		attackTimer_ = 0;
	}

	for (shared_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update(player);
	}

	if (state_ != nullptr)
	{
		state_->Update(this);
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

Vector3 Enemy::GetWorldPosition()
{
	return Vector3(
	worldTransform_.matWorld.m[3][0],
	worldTransform_.matWorld.m[3][1],
	worldTransform_.matWorld.m[3][2]
	);
}

void Enemy::OnCollision(uint32_t id)
{
	id;
	isDeadFlag_ = true;
}

void Enemy::ChangeState(unique_ptr<IEnemyState> state)
{
	state_ = move(state);

}
