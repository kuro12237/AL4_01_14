#include "GameObject3dTest.h"

void GameObject3dTestScene::Initialize()
{


	gameTestobjA = make_unique<Game3dObject>();
	gameTestobjB = make_unique<Game3dObject>();

	gameTestobjA->Create();
	gameTestobjB->Create();

	worldTransformA_.Initialize();
	worldTransformB_.Initialize();
	worldTransformB_.translate.x = 2.0f;
	view_.Initialize();
}

void GameObject3dTestScene::Update(GameManager* Scene)
{
	Scene;
	uint32_t testModel = ModelManager::LoadObjectFile("House");
	uint32_t testGroundModelHandle = ModelManager::LoadObjectFile("TestGround");


	if (Input::PushKey(DIK_P))
	{
		gameTestobjA->SetModel(testModel);
	}
	else
	{
		gameTestobjA->SetModel(testGroundModelHandle);
	}

	gameTestobjB->SetModel(testModel);

	worldTransformA_.UpdateMatrix();
	worldTransformB_.UpdateMatrix();
	view_.UpdateMatrix();
}

void GameObject3dTestScene::Back2dSpriteDraw()
{
}

void GameObject3dTestScene::Object3dDraw()
{
	gameTestobjA->Draw(worldTransformA_, view_);
	gameTestobjB->Draw(worldTransformB_, view_);

}

void GameObject3dTestScene::Flont2dSpriteDraw()
{
}
