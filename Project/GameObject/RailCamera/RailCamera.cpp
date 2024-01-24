#include "RailCamera.h"

void RailCamera::Initialize(Vector3 pos)
{
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	viewProjection_.Initialize();
	viewProjection_.UpdateMatrix();

	controlPoints_ = {
		{0,  0,  2  },
		{0, 0, 4 },
		{0, 0, 8 },
		{0, 5, 16 },
		{0, 0,  32},
		{0, 5, 64 },
		{0, 10, 96},
		{-0,5,128},
		{-0,0,0}
	};

	uint32_t modelHandle = ModelManager::LoadObjectFile("controlPoint");
	shared_ptr<Game3dObject>gameobj_ = nullptr;
	gameobj_ = make_shared<Game3dObject>();
	gameobj_->Create();
	gameobj_->SetModel(modelHandle);
	gameobj_->SetColor({ 1,0,0,1 });
	for (int i = 0; i < controlPoints_.size(); i++)
	{
		const float scale = 0.01f;
		WorldTransform linetransform{};
		linetransform.Initialize();
		linetransform.scale = { scale,scale,scale };
		linetransform.translate = controlPoints_[i];

		pointWorldTransforms_.push_back(linetransform);
		pointGameObjects_.push_back(gameobj_);
	}

}

// Catmull-Romスプライン補間関数
Vector3 RailCamera::CatmullRomInterpolation(int index, float t) {
	const uint32_t kSelect = uint32_t(controlPoints_.size() - 1);
	return VectorTransform::Catmull_Rom(
		controlPoints_[(index - 1 + kSelect) % kSelect],
		controlPoints_[index],
		controlPoints_[(index + 1) % kSelect],
		controlPoints_[(index + 2) % kSelect],
		t
	);
}

void RailCamera::Update() {

	const uint32_t kSelect = uint32_t(controlPoints_.size() - 1);

	if ( targetSelect_ >= kSelect)
	{
		eyeSelect_ = 0;
		targetSelect_ = 0;
		eyet_ = 0.0f;
		targett_ = 0.1f;
		return;
	}

	UpdateParameter(eyet_, eyeSelect_);
	UpdateParameter(targett_, targetSelect_);

	eye_ = CatmullRomInterpolation(eyeSelect_, eyet_);
	target_ = CatmullRomInterpolation(targetSelect_, targett_);

	Vector3 rotate = VectorTransform::Normalize(VectorTransform::Subtruct(target_, eye_));
	//ワールドに変換
	worldTransform_.translate = eye_;

	float velocityXZ = sqrt(rotate.x * rotate.x + rotate.z * rotate.z);
	float heightY = -rotate.y;

	worldTransform_.rotation.y = std::atan2(rotate.x, rotate.z);
	worldTransform_.rotation.x = std::atan2(heightY, velocityXZ);

	worldTransform_.matWorld = MatrixTransform::AffineMatrix(
		worldTransform_.scale, worldTransform_.rotation, worldTransform_.translate);
	Matrix4x4 rx = MatrixTransform::RotateXMatrix(worldTransform_.rotation.x);
	Matrix4x4 ry = MatrixTransform::RotateXMatrix(worldTransform_.rotation.y);
	Matrix4x4 rz = MatrixTransform::RotateXMatrix(worldTransform_.rotation.z);

	Matrix4x4 rXYZ = MatrixTransform::RotateXYZMatrix(worldTransform_.rotation.y, -worldTransform_.rotation.x, worldTransform_.rotation.z);
	Matrix4x4 S = MatrixTransform::ScaleMatrix(worldTransform_.scale);
	Matrix4x4 T = MatrixTransform::TranslateMatrix(worldTransform_.translate);

	worldTransform_.matWorld = MatrixTransform::Multiply(S, MatrixTransform::Multiply(rXYZ, T));

	//viewに変換
	for (int i = 0; i < pointWorldTransforms_.size(); i++)
	{
		pointWorldTransforms_[i].matWorld=MatrixTransform::AffineMatrix(
		pointWorldTransforms_[i].scale, pointWorldTransforms_[i].rotation, pointWorldTransforms_[i].translate);
		pointWorldTransforms_[i].TransfarMatrix();
	}

	viewProjection_.matView_ = MatrixTransform::Inverse(worldTransform_.matWorld);
	worldTransform_.ParentUpdate();
}

void RailCamera::Draw(ViewProjection view)
{
	int c = 0;
	for (int i = 0; i < pointGameObjects_.size(); i++)
	{
		pointGameObjects_[i]->Draw(pointWorldTransforms_[c], view);
		c++;
	}
}

void RailCamera::UpdateParameter(float& param, uint32_t& selctIndex)
{
	const uint32_t kSelect = uint32_t(controlPoints_.size() - 1);
	const float kFlame = 480.0f;

	if (selctIndex != kSelect) 
	{
		param += 1.0f / kFlame;

		if (param >= 1.0f) 
		{
			selctIndex++;
			param = 0.0f;
		}
	}
};