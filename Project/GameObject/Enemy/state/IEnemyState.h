#pragma once

class Enemy;
class IEnemyState
{
public:
	virtual ~IEnemyState() {};

	virtual void Update(Enemy * enemy) = 0;


private:

};


