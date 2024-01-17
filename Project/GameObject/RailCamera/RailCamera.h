#pragma once
#include"Game3dObject.h"

class RailCamera
{
public:
	RailCamera() {};
	~RailCamera() {};

	void Initialize();


	void Update();

	WorldTransform const &GetWorldTransform() { return worldTransform_; }

	ViewProjection GetViewProjection() { return viewProjection_; }

private:

	ViewProjection viewProjection_ = {};
	WorldTransform worldTransform_ = {};

};

