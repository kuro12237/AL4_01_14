#include "TestSphere.h"

void TestSpere::Initialize()
{
	modelHandle_ = ModelManager::LoadObjectFile("TestSphere");
	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	gameObject_->SetModel(modelHandle_);
	gameObject_->UseLight(true);
	worldTransfrom_.Initialize();
}

void TestSpere::Update()
{
	worldTransfrom_.UpdateMatrix();
}

void TestSpere::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransfrom_, view);
}
