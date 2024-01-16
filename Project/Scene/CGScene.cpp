#include "CGScene.h"

void CGScene::Initialize()
{
	testGround_ = make_unique<TestGround>();
	testGround_->Initialize();
	
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0,2.0f,-25.0f };

	LeftLight_ = make_unique<LeftLight>();
	LeftLight_->Initialize();
}

void CGScene::Update(GameManager* Scene)
{
	Scene;
	LeftLight_->Update();
	testGround_->Update();
	viewProjection_.UpdateMatrix();
}

void CGScene::Back2dSpriteDraw()
{
}

void CGScene::Object3dDraw()
{
	testGround_->Draw(viewProjection_);
}

void CGScene::Flont2dSpriteDraw()
{
}
