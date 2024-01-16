#include "GameScene.h"

void GameScene::Initialize()
{

	viewProjection_.Initialize({ 0.0f,0.0f,0.0f }, { 0.0f,2.0f,-32.0f });
	viewProjection_.UpdateMatrix();
	
	player_ = make_unique<Player>();
	player_->Initialize();

	skydome_ = make_unique<Skydome>();
	skydome_->Initialize();
}

void GameScene::Update(GameManager* Scene)
{
	Scene;

	player_->Update();
	skydome_->Update();

	viewProjection_.UpdateMatrix();
}

void GameScene::Back2dSpriteDraw()
{
}

void GameScene::Object3dDraw()
{
	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
}

void GameScene::Flont2dSpriteDraw()
{
}
