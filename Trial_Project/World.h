#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>
#include "KeyList.h"
#include "Entity.h"
#include "Aircraft.h"
#include "ResourceHolder.hpp"
#include "Category.h"
#include "Projectile.h"
#include <iostream>
#ifndef __WORLD__
#define __WORLD__
class World
{
public:
	World(sf::RenderWindow&);
	~World();
	void createEntity(KeyList::ID);
	void addEntity(Entity&);
	void deleteEntity(long ID);
	void generateBackground(KeyList::ID);
	void renderEntity(sf::RenderWindow&);
	void drawEntitySprite(Entity, sf::RenderWindow&);
	void updateEntity(sf::Time);
	void setEntityMovementStatus(sf::Keyboard::Key, bool);
	void drawBackground(sf::RenderWindow&);
	unsigned int getCategory();
	Entity& fetchEntity(long);
	int searchEntity(long);
	void updateEntityPosition(Entity&,sf::Time);
	std::vector<long> checkEntityCollision();
	bool checkBorderCollision(char,char);
	void scrollBackground(sf::Time);
	void checkForClearance(long);
	long getHighestID();
	void loadResources();
	void spawnEnemy();
	sf::Vector2f generateEnemyPosition();
private:
	long generateEntityID();
public:
	std::vector<Entity> entityList;
private:
	Aircraft player;
	Projectile projectile;
	Entity background,background2;
	ResourceHolder<sf::Texture, KeyList::ID> mTexture;
	sf::View mWorldView;
	sf::FloatRect mWorldBounds;
	sf::Texture texture;
};
#endif