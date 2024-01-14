#include "Hammer.h"

Hammer::Hammer(){

}

void Hammer::Initialize(uint32_t model){
	//金属部分
	mainModel_ = std::make_unique<Game3dObject>();

	mainModel_->Create();
	mainModel_->SetModel(model);

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

#pragma region ワールドトランスフォーム
	//SRT
	const float SCALE = 1.0f;
	worldTransform_.scale = { SCALE,SCALE,SCALE };
	worldTransform_.rotation = { 0.0f,0.0f,0.0f };
	worldTransform_.translate = { 0.0f,1.5f,0.0f };

#pragma endregion
}

void Hammer::Update(){
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void Hammer::Draw(ViewProjection viewProjection){
	mainModel_->Draw(worldTransform_, viewProjection);
}

Hammer::~Hammer(){

}
