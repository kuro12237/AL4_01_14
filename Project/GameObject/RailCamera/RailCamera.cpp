#include "RailCamera.h"

void RailCamera::Initialize(Vector3 pos)
{
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	viewProjection_.Initialize();
	//viewProjection_.fov_ = 1200.0f;
	//viewProjection_.translation_ = { 0,0,-32.0f };
	//worldTransform_.translate.z = -32.0f;
	viewProjection_.UpdateMatrix();
}

void RailCamera::Update()
{
	worldTransform_.translate.z += 0.05f;
	worldTransform_.UpdateMatrix();

	viewProjection_.matView_ = MatrixTransform::Inverse(worldTransform_.matWorld);

	ImGui::Begin("RailCamera");
	ImGui::DragFloat3("translate", &worldTransform_.translate.x, -1.0f, 1.0f);
	ImGui::DragFloat3("rotate", &worldTransform_.rotation.x, -10.0f, 10.0f);
	ImGui::End();

}