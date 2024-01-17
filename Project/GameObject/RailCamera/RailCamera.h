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

};

