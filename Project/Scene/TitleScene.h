#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"SceneChangeAnimation/SceneChangeAnimation.h"

class TitleScene :public IScene
{
public:
	TitleScene() {};
	~TitleScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;
private:

	ViewProjection viewProjection_ = {};

	unique_ptr<Sprite>TitleSprite_ = nullptr;
	WorldTransform titleWorldTransform_ = {};

	unique_ptr<Sprite>pushASprite_ = nullptr;
	WorldTransform pushAWorldTransform_ = {};

	int32_t timer_ = 0;
	int32_t kTimer_ = 60;
	bool isPushADrawFlag_ = false;
};