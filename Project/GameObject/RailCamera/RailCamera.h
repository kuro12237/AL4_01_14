#pragma once
#include"Game3dObject.h"

class RailCamera
{
public:
	RailCamera() {};
	~RailCamera() {};

	void Initialize(Vector3 pos);


	void Update();

	const WorldTransform &GetWorldTransform() const { return worldTransform_; }

	ViewProjection GetViewProjection() { return viewProjection_; }

private:

	ViewProjection viewProjection_ = {};
	WorldTransform worldTransform_ = {};

	std::vector<Vector3> controlPoints_;
	
	Vector3 eye_;
	Vector3 target_;
	float eyet_ = 0.0f;
	float targett_ = 0.1f;
	uint32_t eyeSection_ = 0;
	uint32_t targetSection_ = 0;
};

