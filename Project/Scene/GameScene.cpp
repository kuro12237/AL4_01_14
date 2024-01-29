#include "GameScene.h"

void GameScene::Initialize()
{

	viewProjection_.Initialize({ 0.0f,0.0f,0.0f }, { 0.0f,2.0f,-32.0f });
	viewProjection_.UpdateMatrix();

	player_ = make_unique<Player>();
	player_->Initialize();

	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();
	file = FileLoader::CSVLoadFile("Resources/EnemyPop.csv");
	enemyHandle_ = ModelManager::LoadObjectFile("Enemy");

	collisionManager_ = make_unique<CollisionManager>();
	railCamera_ = make_unique<RailCamera>();
	railCamera_->Initialize(player_->GetWorldPosition());
	player_->SetParent(&railCamera_->GetWorldTransform());
	railCameraSpriteON_ = make_unique<Sprite>();
	railCameraSpriteON_->Initialize(new SpriteBoxState);
	uint32_t tex = TextureManager::LoadPngTexture("RailCameraPushA.png");
	railCameraSpriteON_->SetTexHandle(tex);
	railCameraSpriteWorldTransform_.Initialize();

	tex = TextureManager::LoadPngTexture("titleChangePushB.png");
	titleChangeSprite_ = make_unique<Sprite>();
	titleChangeSprite_->Initialize(new SpriteBoxState);
	titleChangeSprite_->SetTexHandle(tex);
	titleChangeWorldTransform_.Initialize();
	titleChangeWorldTransform_.translate.y = 128.0f;
}

void GameScene::Update(GameManager* Scene)
{
	Scene;


	EnemysUpdate();

	player_->Update(viewProjection_);

	skydome_->Update();
	
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		RailCameraOnFlag_ = true;
	}
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_B))
	{
		SceneChangeAnimation::SetChangeFinishFlag(false);
	
	}
	SceneChangeAnimation::Update();

	if (RailCameraOnFlag_)
	{
		railCamera_->Update();
	}

	Collision();

	if (SceneChangeAnimation::GetInstance()->GetSceneChangeFlag())
	{
		Scene->ChangeState(new TitleScene);
		return;
	}
	titleChangeWorldTransform_.UpdateMatrix();
	viewProjection_.matView_ = railCamera_->GetViewProjection().matView_;
	viewProjection_.matProjection_ = railCamera_->GetViewProjection().matProjection_;
	railCameraSpriteWorldTransform_.UpdateMatrix();
	viewProjection_.TransfarMatrix();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	player_->Draw(viewProjection_);

	for (shared_ptr<Enemy>& enemy : enemys_)
	{
		enemy->Draw(viewProjection_);
	}
	skydome_->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
	railCameraSpriteON_->Draw(railCameraSpriteWorldTransform_, viewProjection_);
	titleChangeSprite_->Draw(titleChangeWorldTransform_, viewProjection_);
	player_->FrontDraw(viewProjection_);

	SceneChangeAnimation::Draw(viewProjection_);
}

void GameScene::EnemySpown()
{

	if (EnemyWaitFlag_)
	{
		WaitTimer_--;
		if (WaitTimer_ <= 0)
		{
			EnemyWaitFlag_ = false;
		}
		return;
	}

	std::string line;


	while (std::getline(file, line))
	{

		std::istringstream line_stream(line);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0)
		{
			continue;
		}
		//POPコマンド
		if (word.find("POP") == 0)
		{
			Vector3 pos;
			std::getline(line_stream, word, ',');
			pos.x = (float)std::atof(word.c_str());

			std::getline(line_stream, word, ',');
			pos.y = (float)std::atof(word.c_str());

			std::getline(line_stream, word, ',');
			pos.z = (float)std::atof(word.c_str());
			EnemyPop(pos);
		}
		else if (word.find("WAIT") == 0)
		{
			std::getline(line_stream, word, ',');
			int32_t waitTimer = atoi(word.c_str());
			EnemyWaitFlag_ = true;
			WaitTimer_ = waitTimer;

			break;
		}

	}
}

void GameScene::EnemyPop(Vector3 pos)
{
	shared_ptr<Enemy>enemy = make_shared<Enemy>();
	enemy->Initialize(pos,enemyHandle_);
	enemys_.push_back(enemy);
}

void GameScene::EnemysUpdate()
{
	EnemySpown();

	//enemykill
	enemys_.remove_if([](shared_ptr<Enemy> enemy) {
		if (enemy->GetIsDeadFlag()) {
			enemy.reset();
			return true;
		}
		return false;
		});


	for (shared_ptr<Enemy>& enemy : enemys_)
	{
		enemy->Update(player_.get());
	}

}

void GameScene::Collision()
{
	collisionManager_->ClliderClear();

	collisionManager_->ColliderAABBPushBack(player_.get());
	//playerと当たっている可能性あり

	for (shared_ptr<PlayerBullet>& bullet : player_->GetBullets_())
	{
		collisionManager_->ColliderAABBPushBack(bullet.get());
    }

	for (shared_ptr<Enemy>& enemy : enemys_)
	{
		collisionManager_->ColliderAABBPushBack(enemy.get());

		for (shared_ptr<EnemyBullet>& bullet : enemy->GetBulletsList())
		{
			collisionManager_->ColliderAABBPushBack(bullet.get());
		}
	}
	collisionManager_->CheckAllCollision();
}

