#include "GameManager.h"

GameManager::GameManager()
{
	Cleyera::Initialize();

	WinApp::SetTiTleName(L"CLEYERA");
	Scene_ = new CGScene();

	Scene_->Initialize();
}

GameManager::~GameManager()
{
	delete Scene_;
	Cleyera::Finalize();
}

void GameManager::Run()
{
	while (WinApp::WinMsg())
	{
		Cleyera::BeginFlame();
	
		ImGui::Begin("CGTest");
		
		LightingManager::ClearList();
		
		Scene_->Update(this);

		LightingManager::TransfarBuffers();
		
		ImGui::End();
		
		Scene_->Back2dSpriteDraw();
		Scene_->Object3dDraw();
		Scene_->Flont2dSpriteDraw();
	
		Cleyera::EndFlame();
	}
}

void GameManager::ChangeState(IScene *newScene)
{
	DebugTools::ClearCommand();

	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();
	return;
}
