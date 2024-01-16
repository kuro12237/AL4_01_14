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
}

void GameScene::Update(GameManager* Scene)
{
	Scene;
	EnemySpown();

	player_->Update();
	skydome_->Update();

	for (shared_ptr<Enemy>& enemy : enemys_)
	{
		enemy->Update();
	}

	viewProjection_.UpdateMatrix();
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
