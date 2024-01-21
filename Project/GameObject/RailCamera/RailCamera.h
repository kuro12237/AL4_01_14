#pragma once
#include"Game3dObject.h"

class RailCamera
{
public:
	RailCamera() {};
	~RailCamera() {};

	void Initialize(Vector3 pos);


	void Update();

	void Draw(ViewProjection view);

	const WorldTransform &GetWorldTransform() const { return worldTransform_; }

	ViewProjection GetViewProjection() { return viewProjection_; }

private:

	ViewProjection viewProjection_ = {};
	WorldTransform worldTransform_ = {};

	Matrix4x4 CreateView(Vector3 target, Vector3 eye);
	void UpdateParameter(float& parameter, uint32_t& selctIndex);
	Vector3 CatmullRomInterpolation(int index, float t);

	vector<Vector3> controlPoints_;

	Vector3 eye_{};
	Vector3 target_{};
	float eyet_ = 0.0f;
	float targett_ = 0.1f;
	uint32_t eyeSelect_ = 0;
	uint32_t targetSelect_ = 0;

	vector<shared_ptr<Game3dObject>>pointGameObjects_{};
	vector<WorldTransform>pointWorldTransforms_{};

};

