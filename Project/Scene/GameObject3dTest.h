#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"
#include"AudioManager.h"
#include"FileLoader.h"
#include"CollisionManager.h"
#include"Particle/Particle.h"
#include"ModelManager.h"
#include"Light/Light.h"

#include"GameObject/FireParticles/FireParticle.h"
#include"Game3dObject.h"

class GameObject3dTestScene :public IScene
{
public:
	GameObject3dTestScene() {};
	~GameObject3dTestScene() {};


	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	unique_ptr<Game3dObject>gameTestobjA = nullptr;

	unique_ptr<Game3dObject>gameTestobjB = nullptr;

	WorldTransform worldTransformA_ = {};
	WorldTransform worldTransformB_ = {};

	ViewProjection view_;
};
