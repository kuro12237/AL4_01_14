#pragma once
#include <ViewProjection.h>
#include <WorldTransform.h>
#include <Game3dObject.h>

#include <memory>

class Hammer {
public:
	//コンストラクタ
	Hammer();

	//初期化
	void Initialize(uint32_t model);

	//更新
	void Update();

	//描画
	void Draw(ViewProjection viewProjection);

	//デストラクタ
	~Hammer();


public:
	//アクセッサ
	void SetRotate(Vector3 rotate) {
		this->worldTransform_.rotation = rotate;
	}
	Vector3 GetRotate() {
		return worldTransform_.translate;
	}


private:
	//ワールドトランスフォーム
	WorldTransform worldTransform_ = {};

	//モデル
	//金属部分
	std::unique_ptr<Game3dObject> mainModel_ = nullptr ;






};

