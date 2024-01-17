#include "SkyDome.h"

void Skydome::Initialize()
{

	modelHandle_ = ModelManager::LoadObjectFile("SkyDome");

	gameObject_ = make_unique<Game3dObject>();
	gameObject_->Create();
	
	gameObject_->SetModel(modelHandle_);

	worldTransform_.Initialize();

}

void Skydome::Update()
{
	gameObject_->SetUvScale({ -1.0f,1.0f,1.0f });
	worldTransform_.UpdateMatrix();

}

void Skydome::Draw(ViewProjection view)
{
	gameObject_->Draw(worldTransform_, view);
}
