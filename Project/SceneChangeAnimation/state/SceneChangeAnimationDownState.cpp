#include "SceneChangeAnimationDownState.h"

void SceneChangeAnimationDownState::Update(SceneChangeAnimation* state)
{
	nowFlame_ += 0.8f;

	Move(state);

	if (state->Getcolor().w >= endColor_.w)
	{
		state->SetSceneChangeFlag(true);
		state->SetChangeEndFlag(true);
		state->SetChangeStartFlag(false);
	}
}

void SceneChangeAnimationDownState::Move(SceneChangeAnimation* state)
{
	Vector4 color = state->Getcolor();
	color.w = color.w + 0.01f;
	state->SetColor_(color);
}

Vector3 SceneChangeAnimationDownState::BounseLeap(Vector3 s, Vector3 e, float t)
{
	return VectorTransform::Lerp(s, e, VectorTransform::easeOutBounce(t));

}
