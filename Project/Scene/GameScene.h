#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"GameObject/Player/Player.h"
#include"GameObject/Stage/Stage.h"


class GameScene :public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	ViewProjection viewProjection_ = {};

	unique_ptr<Player>player_ = nullptr;
	unique_ptr<Stage>stage_ = nullptr;

	
};