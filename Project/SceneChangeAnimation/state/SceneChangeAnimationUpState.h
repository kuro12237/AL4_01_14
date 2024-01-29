#pragma once
#include"ISceneChangeAnimationState.h"
#include"SceneChangeAnimation/SceneChangeAnimation.h"
#include"VectorTransform.h"

class SceneChangeAnimationUpState :public ISceneChangeAnimationState
{
public:
	SceneChangeAnimationUpState() {};
	~SceneChangeAnimationUpState() {};

	void Update(SceneChangeAnimation* state)override;

private:

	void Move(SceneChangeAnimation* state);

	
	double nowFlame_ = 0.0f;
	float endFlame_ = 600.0f;

	Vector4 endColor_ = { 1.0f,1.0f,1.0f,0.0f };

};