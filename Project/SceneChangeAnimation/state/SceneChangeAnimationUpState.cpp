#include "SceneChangeAnimationUpState.h"

void SceneChangeAnimationUpState::Update(SceneChangeAnimation* state)
{
	nowFlame_ += 0.8f;

	Move(state);

	if (state->Getcolor().w >= endColor_.y)
	{
		state->SetChangeFinishFlag(true);
		state->SetChangeEndFlag(false);
	}
}

void SceneChangeAnimationUpState::Move(SceneChangeAnimation* state)
{
	Vector4 color = state->Getcolor();
	color.w = color.w - 0.01f;
	state->SetColor_(color);

}
