#pragma once
#include"Cleyera.h"
#include"IScene.h"
#include"MTScene.h"
#include"../DebugTools/Camera/DebugCamera.h"
#include"GameObject3dTest.h"
#include"GameScene.h"

class GameManager
{
public:

	GameManager();
	~GameManager();

    void Run();
    void ChangeState(IScene *newScene);

private:

	IScene* Scene_ = nullptr;

};

