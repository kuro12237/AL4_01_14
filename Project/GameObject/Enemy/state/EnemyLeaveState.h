#pragma once
#include"IEnemyState.h"
#include"GameObject/Enemy/Enemy.h"

class EnemyLeaveState:public IEnemyState
{
public:
	EnemyLeaveState() {};
	~EnemyLeaveState() {};

	void Update(Enemy* enemy);

private:

};

