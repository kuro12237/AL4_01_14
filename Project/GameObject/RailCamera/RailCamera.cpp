#include "RailCamera.h"

void RailCamera::Initialize()
{
	worldTransform_.Initialize();
	
	viewProjection_.Initialize();
	//viewProjection_.fov_ = 1200.0f;
	viewProjection_.translation_ = { 0,0,-32.0f };
	//worldTransform_.translate.z = -32.0f;
}

void RailCamera::Update()
{

	//worldTransform_.translate.z += 0.05f;
	viewProjection_.translation_.z += 0.05f;
	worldTransform_.UpdateMatrix();
	viewProjection_.matView_ = MatrixTransform::Inverse(worldTransform_.matWorld);
	viewProjection_.UpdateMatrix();

	ImGui::Begin("RailCamera");
	ImGui::DragFloat3("translate", &viewProjection_.translation_.x, -100.0f, 100.0f);
	ImGui::DragFloat3("rotate", &viewProjection_.rotation_.x, -10.0f, 10.0f);
	ImGui::End();

}