#include "EnemyApprochState.h"

void EnemeyApprochState::Update(Enemy* state)
{
	translate_ = state->GetWorldTranslate();

	translate_.z -= 0.2f;

	state->SetWorldTranslate(translate_);

	if (translate_.z < 32.0f)
	{
		state->ChangeState(make_unique<EnemyLeaveState>());
	}

}
