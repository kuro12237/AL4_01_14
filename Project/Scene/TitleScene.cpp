#include "TitleScene.h"

void TitleScene::Initialize()
{

	SceneChangeAnimation::Initialize();
	viewProjection_.Initialize();

	uint32_t texHandle = TextureManager::LoadPngTexture("Title/Title.png");
	Vector2 texSize = TextureManager::GetTextureSize(texHandle);
	texSize.x *= -0.5f;
	texSize.y *= -0.5f;

	TitleSprite_ = make_unique<Sprite>();
	TitleSprite_->Initialize(new SpriteBoxState,texSize);
	TitleSprite_->SetTexHandle(texHandle);
	titleWorldTransform_.Initialize();
	titleWorldTransform_.translate = { 640.0f,180.0f };

	texHandle = TextureManager::LoadPngTexture("Title/PUSH_A.png");
	texSize = TextureManager::GetTextureSize(texHandle);
	texSize.x *= -0.5f;
	texSize.y *= -0.5f;
	pushASprite_ = make_unique<Sprite>();
	pushASprite_->Initialize(new SpriteBoxState, texSize);
	pushASprite_->SetTexHandle(texHandle);
	pushAWorldTransform_.Initialize();
	pushAWorldTransform_.translate = { 640,570.0f };
}

void TitleScene::Update(GameManager* Scene)
{
	if (Input::PushBottonPressed(XINPUT_GAMEPAD_A))
	{
		SceneChangeAnimation::SetChangeFinishFlag(false);
	}
	SceneChangeAnimation::Update();

	if (SceneChangeAnimation::GetInstance()->GetSceneChangeFlag())
	{
		Scene->ChangeState(new GameScene);
		return;
	}

	timer_++;
	if (timer_>=kTimer_)
	{
		if (!isPushADrawFlag_)
		{
			isPushADrawFlag_ = true;
		}
		else
		{
			isPushADrawFlag_ = false;
		}
		timer_ = 0;
	}

	titleWorldTransform_.UpdateMatrix();
	pushAWorldTransform_.UpdateMatrix();
	viewProjection_.UpdateMatrix();
}

void TitleScene::Back2dSpriteDraw()
{
}

void TitleScene::Object3dDraw()
{
}

void TitleScene::Flont2dSpriteDraw()
{
	TitleSprite_->Draw(titleWorldTransform_, viewProjection_);

	if (isPushADrawFlag_)
	{
		pushASprite_->Draw(pushAWorldTransform_, viewProjection_);
	}
	SceneChangeAnimation::Draw(viewProjection_);
}
