#pragma once
#include"IEnemyState.h"
#include"GameObject/Enemy/Enemy.h"
#include"EnemyLeaveState.h"

class EnemeyApprochState:public IEnemyState
{
public:
	EnemeyApprochState() {};
	~EnemeyApprochState() {};

	void Update(Enemy* state);

private:

	Vector3 translate_ = {};

};