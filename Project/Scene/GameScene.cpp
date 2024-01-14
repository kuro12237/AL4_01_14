#include "GameScene.h"

void GameScene::Initialize()
{

	viewProjection_.Initialize({ 0.5f,0.0f,0.0f }, { 0.0f,8.9f,-12.0f });
	viewProjection_.UpdateMatrix();
	
	player_ = std::make_unique<Player>();
	uint32_t playerModel = ModelManager::LoadObjectFile("House");
	uint32_t hammerModel[2] = {};
	hammerModel[0] = ModelManager::LoadObjectFile("MainHammer");
	hammerModel[1] = ModelManager::LoadObjectFile("HammerStick");

	player_->Initialize(playerModel, hammerModel[1]);

	stage_ = std::make_unique<Stage>();
	uint32_t stageModel[3] = {};
	stageModel[0] = ModelManager::LoadObjectFile("box1");
	stageModel[1] = ModelManager::LoadObjectFile("box2");
	stageModel[2] = ModelManager::LoadObjectFile("box3");

	stage_->Initialize(stageModel);


}

void GameScene::Update(GameManager* Scene)
{
	Scene;


	
	player_->Update();
	stage_->Update();

	viewProjection_.UpdateMatrix();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	player_->Draw(viewProjection_);
	stage_->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
