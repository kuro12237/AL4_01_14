#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"AudioManager.h"
#include"FileLoader.h"
#include"CollisionManager.h"
#include"Particle/Particle.h"
#include"Quaternion/QuaternionTransform.h"

class MTScene :public IScene
{
public:
	MTScene() {};
	~MTScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	Vector3 axis_{ 1.0f ,1.0f ,1.0f };
	float angle = 0.44f;
	Matrix4x4 rotateMatrix_ = {};

	unique_ptr<Model>model_ = nullptr;
	WorldTransform worldTransform_ = {};
	ViewProjection viewProjection_ = {};
};