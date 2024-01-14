#include "Player.h"

#include "Input.h"
#include "VectorTransform.h"
//コンストラクタ
Player::Player(){

}

//初期化
void Player::Initialize(uint32_t playerModel, uint32_t hammerModel){

	model_ = std::make_unique<Game3dObject>();
	model_->Create();
	model_->SetModel(playerModel);

	//ハンマー
	hammer_ = std::make_unique<Hammer>();
	hammer_->Initialize(hammerModel);

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

#pragma region ワールドトランスフォーム
	//SRT
	const float SCALE = 1.0f;
	worldTransform_.scale = { SCALE,SCALE,SCALE };
	worldTransform_.rotation = { 0.0f,0.0f,0.0f };
	worldTransform_.translate = { 0.0f,1.5f,0.0f };

#pragma endregion

	//初速度
	
	velocity_ = { 0.0f,initialVelocity_,0.0f };
	//加速度
	acceleration_ = { 0.0f,-0.03f,0.0f };


}

void Player::Attack() {
	hammer_->Update();
}

//更新
void Player::Update(){
	//何も押していない時は0.0f
	Vector3 move = { 0.0f,0.0f,0.0f };
	const float MOVE_AMOUNT_ = 0.1f;

	ImGui::Begin("Player");
	ImGui::SliderFloat3("Translate", &worldTransform_.translate.x, -10.0f, 10.0f);
	ImGui::End();

	
#pragma region ボタン処理
	//PushKeyPressedはTriggerのこと

	#pragma region 移動
	//上を押すと前に進む
	if (Input::GetInstance()->PushKey(DIK_UP) == true) {
		move.z += MOVE_AMOUNT_;
	}

	//下を押すと前に進む
	if (Input::GetInstance()->PushKey(DIK_DOWN) == true) {
		move.z -= MOVE_AMOUNT_;
	}

	//右を押すと前に進む
	if (Input::GetInstance()->PushKey(DIK_RIGHT) == true) {
		move.x += MOVE_AMOUNT_;
	}

	//左を押すと前に進む
	if (Input::GetInstance()->PushKey(DIK_LEFT) == true) {
		move.x -= MOVE_AMOUNT_;
	}
	#pragma endregion

	#pragma region ジャンプ
	//スペースを押していない時は勿論ジャンプしない
	//押した瞬間
	if ((Input::GetInstance()->PushKeyPressed(DIK_SPACE) == true)&&(worldTransform_.translate.y == GROUND_TRANSLATE_)) {
		ImGui::Begin("Jump");
		ImGui::End();
		isJump = true;
	}

	//ジャンプしている時
	if (isJump == true) {
		velocity_ =VectorTransform::Add(velocity_, acceleration_);
		move.y = velocity_.y;
	}

	//めり込み厳禁
	if (worldTransform_.translate.y < GROUND_TRANSLATE_) {
		worldTransform_.translate.y = GROUND_TRANSLATE_;
		//velocity初期化忘れずに
		velocity_.y = initialVelocity_;
		isJump = false;
	}

	#pragma endregion
	
	#pragma region 攻撃
	if (Input::GetInstance()->PushKeyPressed(DIK_CAPITAL) == true) {
		Attack();
	}


	#pragma endregion

#pragma endregion

	//計算
	//ベクトルの計算をするときはVectorTransformw.hをインクルード
	worldTransform_.translate = VectorTransform::Add(worldTransform_.translate, move);

	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

//描画
void Player::Draw(ViewProjection viewProjection){
	//モデルの描画
	//これなしの場合一瞬GROUND_TRANSLATE_-OFFSETより下が表示されて気になるので入れた
	const float OFFSET = 0.1f;
	if (worldTransform_.translate.y >= GROUND_TRANSLATE_-OFFSET) {
		model_->Draw(worldTransform_, viewProjection);
	}
	hammer_->Draw(viewProjection);
	if (isAttack_ == true) {
		
	}
	
}

//デストラクタ
Player::~Player(){


}
