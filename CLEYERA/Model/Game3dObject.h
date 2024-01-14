#pragma once
#include"ModelManager.h"

class Game3dObject
{
public:
	Game3dObject() {};
	~Game3dObject() {};

	void Create();

	void SetModel(uint32_t index);

	void Draw(WorldTransform worldTransform,ViewProjection view);


#pragma region Set

	void SetUvScale(Vector3 s) { uvScale_ = s; }
	void SetUvRotate(Vector3 r) { uvRotate = r; }
	void SetTranslate(Vector3 t) { uvTranslate = t; }

	void SetColor(Vector4 color) { color_ = color; }

	void SetShininess(float s) { shininess = s; }

	void SetTexHandle(uint32_t index) { texHandle_ = index; }

	void UseLight(bool flag) { UseLight_ = flag; }
#pragma endregion


private:

	Model *model_ = nullptr;
	uint32_t prevModelIndex_ = 0;

	ComPtr<ID3D12Resource> MaterialBuffer_ = nullptr;
	Vector4 color_ = { 1,1,1,1 };
	
	Vector3 uvScale_ = { 1,1,1 };
	Vector3 uvRotate = { 0,0,0 };
	Vector3 uvTranslate = { 0,0,0 };
	float shininess = 70.0f;

	bool UseLight_ = false;

	uint32_t texHandle_ = 0;

};