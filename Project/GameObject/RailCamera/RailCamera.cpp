#include "RailCamera.h"

void RailCamera::Initialize(Vector3 pos)
{
	worldTransform_.Initialize();
	worldTransform_.translate = pos;
	viewProjection_.Initialize();
	viewProjection_.UpdateMatrix();

	controlPoints_ = {
		{0,  0,  0  },
		{4, 5, 8 },
		{8, 10, 16 },
		{12, 5, 16 },
		{16, 0,  16},
		{12, 5, 12 },
		{8, 10, 10},
		{-20,5,-10},
		{-10,0,5}
	};

	uint32_t modelHandle = ModelManager::LoadObjectFile("controlPoint");
	shared_ptr<Game3dObject>gameobj_ = nullptr;
	gameobj_ = make_shared<Game3dObject>();
	gameobj_->Create();
	gameobj_->SetModel(modelHandle);

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
	const uint32_t kSelection = uint32_t(controlPoints_.size() - 1);
	return VectorTransform::Catmull_Rom(
		controlPoints_[(index - 1 + kSelection) % kSelection],
		controlPoints_[index],
		controlPoints_[(index + 1) % kSelection],
		controlPoints_[(index + 2) % kSelection],
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
	worldTransform_.rotation.y = atan2(rotate.x, rotate.z);
	float roateLength = VectorTransform::Length({ rotate.x, 0, rotate.z });
	worldTransform_.rotation.x = atan2(-rotate.y, roateLength);

	worldTransform_.matWorld = MatrixTransform::AffineMatrix(
		worldTransform_.scale, worldTransform_.rotation, worldTransform_.translate);
	//viewに変換
	viewProjection_.UpdateMatrix();
	viewProjection_.matView_ = CreateView(target_, eye_);

	viewProjection_.TransfarMatrix();

	for (int i = 0; i < pointWorldTransforms_.size(); i++)
	{
		pointWorldTransforms_[i].matWorld=MatrixTransform::AffineMatrix(
		pointWorldTransforms_[i].scale, pointWorldTransforms_[i].rotation, pointWorldTransforms_[i].translate);
		pointWorldTransforms_[i].TransfarMatrix();
	}

	ImGui::Begin("Camera");
	ImGui::DragFloat3("translate", &worldTransform_.translate.x, 0.01f);
	ImGui::DragFloat3("rotate", &worldTransform_.rotation.x, 0.01f);
	ImGui::Text("%d", controlPoints_.size());
	ImGui::Text("eyeSelect :: %d targetSelect :: %d", eyeSelect_, targetSelect_);
	ImGui::End();

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

Matrix4x4 RailCamera::CreateView(Vector3 target, Vector3 eye)
{
	Vector3 z = VectorTransform::Subtruct(target, eye);
	z = VectorTransform::Normalize(z);
	//xの外積
	Vector3 x = VectorTransform::Cross({ 0.0f, 1.0f, 0.0f }, z);
	x = VectorTransform::Normalize(x);
	//yの外積
	Vector3 y = VectorTransform::Cross(z, x);
	y = VectorTransform::Normalize(y);

	//view行列の作成
	Matrix4x4 matrix = MatrixTransform::Identity();;
	matrix.m[0][0] = x.x;
	matrix.m[0][1] = y.x;
	matrix.m[0][2] = z.x;

	matrix.m[1][0] = x.y;
	matrix.m[1][1] = y.y;
	matrix.m[1][2] = z.y;

	matrix.m[2][0] = x.z;
	matrix.m[2][1] = y.z;
	matrix.m[2][2] = z.z;

	matrix.m[3][0] = -VectorTransform::Dot(eye_, x);
	matrix.m[3][1] = -VectorTransform::Dot(eye_, y);
	matrix.m[3][2] = -VectorTransform::Dot(eye_, z);

	return matrix;
}
void RailCamera::UpdateParameter(float& parameter, uint32_t& selctIndex)
{
	const uint32_t kSelection = uint32_t(controlPoints_.size() - 1);
	const float kFlame = 480.0f;

	if (selctIndex != kSelection) {
		parameter += 1.0f / kFlame;
		if (parameter >= 1.0f) {
			parameter = 0.0f;
			selctIndex++;
		}
	}
};