#include <SFML\Graphics.hpp>
#include "Entity.h"
#ifndef __AIRCRAFT__
#define __AIRCRAFT__
class Aircraft:public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor
	};
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;
	bool isFiring;
	float firingRate;
	float firingUpdate;
	bool canFire;
	Type type;
	float velocity;
public:
	unsigned int getCategory()
	{
		if (type == Type::Eagle)
		{
			return Category::AlliedAircraft;
		}
		else
		{
			return Category::EnemyAircraft;
		}
	}
public:
	Aircraft();
	Aircraft(float);
	Aircraft(float, float);
	~Aircraft();
	void setFiringRate(float);
	float getFiringRate();
	void setCanFire(bool);
	bool getCanFire();
	void setFiringUpdate(float);
	float getFiringUpdate();
	void setVelocity(float);
	float getVelocity();
};
#endif