#include "TestLeftLight.h"

void LeftLight::Initialize()
{
}

void LeftLight::Update()
{
	
	if (ImGui::TreeNode("leftLight"))
	{
		ImGui::ColorPicker3("color", &pointLight_.color.x);
		ImGui::DragFloat3("pos", &pointLight_.position.x,-0.5f,0.5f);
		ImGui::DragFloat("decay",&pointLight_.decay);
		ImGui::DragFloat("Intencity", &pointLight_.intencity);
		ImGui::DragFloat("radious", &pointLight_.radious);

		ImGui::TreePop();
	}

	LightingManager::AddList(pointLight_);
}
