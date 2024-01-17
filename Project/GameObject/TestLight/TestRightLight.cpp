#include "TestRightLight.h"

void RightLight::Initialize()
{
	pointLight_.position = { -2.0f,0.5f,-2.0f };
}

void RightLight::Update()
{

	if (ImGui::TreeNode("RightLight"))
	{
		ImGui::ColorPicker3("color", &pointLight_.color.x);
		ImGui::DragFloat3("pos", &pointLight_.position.x, -0.5f, 0.5f);
		ImGui::DragFloat("decay", &pointLight_.decay);
		ImGui::DragFloat("Intencity", &pointLight_.intencity);
		ImGui::DragFloat("radious", &pointLight_.radious);

		ImGui::TreePop();
	}

	LightingManager::AddList(pointLight_);
}