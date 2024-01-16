#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"

#include"GameObject/TestGround/TestGround.h"
#include"GameObject/TestLight/TestLeftLight.h"

class CGScene :public IScene
{
public:
	CGScene() {};
	~CGScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:
	ViewProjection viewProjection_;
    unique_ptr<TestGround>testGround_ = nullptr;

	unique_ptr<LeftLight>LeftLight_ = nullptr;
};