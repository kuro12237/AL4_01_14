#include "EnemyLeaveState.h"

void EnemyLeaveState::Update(Enemy* enemy)
{
	Vector3 translate = enemy->GetWorldTranslate();


	translate.x += 0.1f;

	enemy->SetWorldTranslate(translate);
}
