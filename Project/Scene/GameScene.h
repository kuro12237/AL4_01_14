#pragma once
#include"IScene.h"
#include"GameManager.h"
#include"Input.h"

#include"GameObject/Player/Player.h"
#include"GameObject/SkyDome/SkyDome.h"
#include"GameObject/Enemy/Enemy.h"
#include"FileLoader.h"
#include"CollisionManager.h"
#include"GameObject/RailCamera/RailCamera.h"

class GameScene :public IScene
{
public:
	GameScene() {};
	~GameScene() {};

	void Initialize()override;

	void Update(GameManager* Scene)override;

	void Back2dSpriteDraw()override;
	void Object3dDraw()override;
	void Flont2dSpriteDraw()override;

private:

	void EnemySpown();

	void EnemyPop(Vector3 pos);

	void EnemysUpdate();

	void Collision();


	ViewProjection viewProjection_ = {};

	unique_ptr<Player>player_ = nullptr;
	unique_ptr<RailCamera>railCamera_ = nullptr;
	unique_ptr<Skydome>skydome_ = nullptr;

	list<shared_ptr<Enemy>>enemys_ = {};
	
	std::stringstream file;

	bool EnemyWaitFlag_ = false;
	int32_t WaitTimer_ = 0;
	uint32_t enemyHandle_ = 0;

	unique_ptr<CollisionManager>collisionManager_ = nullptr;

	unique_ptr<Sprite>railCameraSpriteON_ = nullptr;
	WorldTransform railCameraSpriteWorldTransform_ = {};

	unique_ptr<Sprite>titleChangeSprite_ = nullptr;
	WorldTransform titleChangeWorldTransform_ = {};

	bool RailCameraOnFlag_ = false;
};