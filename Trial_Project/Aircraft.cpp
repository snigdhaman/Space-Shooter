#include "Aircraft.h"


Aircraft::Aircraft()
{
	isMovingUp = false;
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;
	canFire = true;
}

Aircraft::Aircraft(float firingRate)
{
	isMovingUp = false;
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;
	canFire = true;
	this->firingRate = firingRate;
}

Aircraft::Aircraft(float posX, float posY)
{
	isMovingUp = false;
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;
	canFire = true;
	setPosition(posX, posY);
}

Aircraft::~Aircraft()
{
}

void Aircraft::setFiringRate(float firingRate)
{
	this->firingRate = firingRate;
}

float Aircraft::getFiringRate()
{
	return firingRate;
}

void Aircraft::setCanFire(bool canFire)
{
	this->canFire = canFire;
}

bool Aircraft::getCanFire()
{
	return canFire;
}

void Aircraft::setFiringUpdate(float firingUpdate)
{
	this->firingUpdate = firingUpdate;
}

float Aircraft::getFiringUpdate()
{
	return firingUpdate;
}

void Aircraft::setVelocity(float velocity)
{
	this->velocity = velocity;
}

float Aircraft::getVelocity()
{
	return velocity;
}