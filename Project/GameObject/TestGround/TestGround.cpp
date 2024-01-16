#include "TestGround.h"

void TestGround::Initialize()
{
	modelhandle_ = ModelManager::LoadObjectFile("TestGround");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelhandle_);
	gameObject_->UseLight(true);
	worldTransform_.Initialize();
}

void TestGround::Update()
{


	worldTransform_.UpdateMatrix();
}

void TestGround::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);

}
