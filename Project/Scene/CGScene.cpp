#include "CGScene.h"

void CGScene::Initialize()
{
	testGround_ = make_unique<TestGround>();
	testGround_->Initialize();
	
	viewProjection_.Initialize();
	viewProjection_.translation_ = { 0,4.0f,-25.0f };
	viewProjection_.rotation_ = { 0.2f,0.0f,0.0f };
	LeftLight_ = make_unique<LeftLight>();
	LeftLight_->Initialize();

	rightLight_ = make_unique<RightLight>();
	rightLight_->Initialize();

	testSphere_ = make_unique<TestSpere>();
	testSphere_->Initialize();
}

void CGScene::Update(GameManager* Scene)
{
	Scene;
	LeftLight_->Update();
	rightLight_->Update();
	testGround_->Update();
	testSphere_->Update();
	viewProjection_.UpdateMatrix();
}

void CGScene::Back2dSpriteDraw()
{
}

void CGScene::Object3dDraw()
{
	testSphere_->Draw(viewProjection_);
	testGround_->Draw(viewProjection_);
}

void CGScene::Flont2dSpriteDraw()
{
}
