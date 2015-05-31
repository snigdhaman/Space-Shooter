#include "Entity.h"


Entity::Entity()
{
}

Entity::~Entity()
{
}

Entity::Entity(long id)
{
	this->id = id;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity()
{
	return mVelocity;
}

void Entity::setPosition(sf::Vector2f &position)
{
	entitySprite.setPosition(position);
}

void Entity::setPosition(float px, float py)
{
	entitySprite.setPosition(px, py);
}

sf::Vector2f Entity::getPosition()
{
	return entitySprite.getPosition();
}

void Entity::setEntityID(long id)
{
	this->id = id;
}

long Entity::getEntityID()
{
	return id;
}

void Entity::setEntityType(int type)
{
	this->entityType = type;
}

int Entity::getEntityType()
{
	return entityType;
}

void Entity::setClearanceFlag(bool clearanceFlag)
{
	this->clearanceFlag = clearanceFlag;
}

bool Entity::getClearanceFlag()
{
	return clearanceFlag;
}