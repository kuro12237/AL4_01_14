#pragma once
#include"ISceneChangeAnimationState.h"
#include"SceneChangeAnimation/SceneChangeAnimation.h"
#include"VectorTransform.h"

class SceneChangeAnimationDownState:public ISceneChangeAnimationState
{
public:
	SceneChangeAnimationDownState() {};
	~SceneChangeAnimationDownState() {};

	void Update(SceneChangeAnimation* state)override;

private:

	void Move(SceneChangeAnimation* state);

    Vector3 BounseLeap(Vector3 s,Vector3 e,float t);

	double nowFlame_ = 0.0f;
	float endFlame_ = 600.0f;

	Vector4 endColor_ = {1,1,1,1};

};



