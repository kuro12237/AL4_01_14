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
	return Vector3(
		s.x + (e.x - s.x) * VectorTransform::easeOutBounce(t),
		s.y + (e.y - s.y) * VectorTransform::easeOutBounce(t),
		s.z + (e.z - s.z) * VectorTransform::easeOutBounce(t)
	);

}
