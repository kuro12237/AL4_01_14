#include "MTScene.h"

void MTScene::Initialize()
{
	model_ = make_unique<Model>();
	model_;
	worldTransform_.Initialize();

	viewProjection_.Initialize({ 0,0,0.0f }, { 0.0f,0.0f,-5.0f });
	viewProjection_.UpdateMatrix();
}

void MTScene::Update(GameManager* Scene)
{
	Scene;
	//rotateMatrix_ = Quaternion::MakeRotateAxisAngle(axis_, angle);
	//axis_ = VectorTransform::Normalize(axis_);

	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };


	Quaternion AnsIdentity = QuaternionTransform::IdentityQuaternion();
	Quaternion AnsConj = QuaternionTransform::Conjugation(q1);
	Quaternion AnsInverse = QuaternionTransform::Inverse(q1);
	Quaternion AnsNormalize = QuaternionTransform::Normalize(q1);
	Quaternion AnsMul1 = QuaternionTransform::Multiply(q1, q2);
	Quaternion AnsMul2 = QuaternionTransform::Multiply(q2, q1);
	float AnsNorm = QuaternionTransform::Norm(q1);
	ImGui::Begin("MT_01_03");

	ImGui::Text("Identity : %0.2f %0.2f %0.2f %0.2f", AnsIdentity.x, AnsIdentity.y, AnsIdentity.z, AnsIdentity.w);
	ImGui::Text("Conjugation: %0.2f %0.2f %0.2f %0.2f", AnsConj.x, AnsConj.y, AnsConj.z, AnsConj.w);
	ImGui::Text("Inverse: %0.2f %0.2f %0.2f %0.2f", AnsInverse.x, AnsInverse.y, AnsInverse.z, AnsInverse.w);
	ImGui::Text("AnsNormalize: %0.2f %0.2f %0.2f %0.2f", AnsNormalize.x, AnsNormalize.y, AnsNormalize.z, AnsNormalize.w);
	ImGui::Text("mul1: %0.2f %0.2f %0.2f %0.2f",AnsMul1.x, AnsMul1.y,AnsMul1.z,AnsMul1.w);
	ImGui::Text("mul2: %0.2f %0.2f %0.2f %0.2f", AnsMul2.x, AnsMul2.y, AnsMul2.z, AnsMul2.w);
	ImGui::Text("norm: %0.2f", AnsNorm);


	ImGui::End();

	

	Matrix4x4 sMat = MatrixTransform::ScaleMatrix(worldTransform_.scale);
	
	Matrix4x4 tMat = MatrixTransform::TranslateMatrix(worldTransform_.translate);
	
	Matrix4x4 matWorld = MatrixTransform::Multiply(sMat, MatrixTransform::Multiply(rotateMatrix_, tMat));
	
	worldTransform_.matWorld = MatrixTransform::Multiply(matWorld, MatrixTransform::Multiply(viewProjection_.matView_, viewProjection_.matProjection_));
	//worldTransform_.UpdateMatrix();

	worldTransform_.TransfarMatrix();
	viewProjection_.UpdateMatrix();
}

void MTScene::Back2dSpriteDraw()
{
}

void MTScene::Object3dDraw()
{
	//model_->Draw(worldTransform_, viewProjection_);
}

void MTScene::Flont2dSpriteDraw()
{
}
