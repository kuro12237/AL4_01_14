#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Game3dObject.h>

#include <memory>
#include "Hammer/Hammer.h"

class Player{
public:
	//コンストラクタ
	Player();

	//初期化
	void Initialize(uint32_t playerModel,uint32_t hammerModel);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection viewProjection);

	//デストラクタ
	~Player();

private:
	void Attack();


public:
	//初速度の設定
	void SetInitialVelocity(float initialVelocity) {
		this->initialVelocity_ = initialVelocity;
	}


private:
	//ワールドトランスフォーム
	WorldTransform worldTransform_ = {};

	//モデル
	std::unique_ptr<Game3dObject> model_ = nullptr;

	//地面
	const float GROUND_TRANSLATE_ = 1.5f;

#pragma region ジャンプ
	//ジャンプしているかどうか
	bool isJump = false;

	//初速度
	float initialVelocity_ = 0.55f;
	Vector3 velocity_ = { 0.0f,0.0f,0.0f };
	//加速度
	Vector3 acceleration_ = { 0.0f,0.0f,0.0f };
	

#pragma endregion



	//ハンマー
	std::unique_ptr<Hammer>hammer_ = nullptr;
	bool isAttack_ = false;

};

