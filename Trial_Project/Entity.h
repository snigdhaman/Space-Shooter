#include <SFML\Graphics.hpp>
#include "SceneNode.h"
#include "Category.h"
#ifndef __ENTITY__
#define __ENTITY__
class Entity:public SceneNode
{
public:
	Entity();
	Entity(long);
	~Entity();
	void setVelocity(sf::Vector2f);
	void setVelocity(float, float);
	sf::Vector2f getVelocity();
	void setPosition(sf::Vector2f&);
	void setPosition(float, float);
	void setRepeated(bool);
	sf::Vector2f getPosition();
	long getEntityID();
	void setEntityID(long);
	void setEntityType(int);
	int getEntityType();
	void setClearanceFlag(bool);
	bool getClearanceFlag();
public:
	sf::Vector2f mVelocity;
	sf::Texture entityTexture;
	sf::Sprite entitySprite;
private:
	long id;
	int entityType;
	bool clearanceFlag;
};
#endif