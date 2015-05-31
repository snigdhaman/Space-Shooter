#include "World.h"


World::World(sf::RenderWindow &mWindow) :mWorldView(mWindow.getDefaultView()), mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 800.f), player(0.5f)
{
}


World::~World()
{
}

void World::createEntity(KeyList::ID id)
{
	if (id == KeyList::ID::Player)
	{
		
		player.entitySprite.setTexture(mTexture.getResource(KeyList::Player));
		player.setPosition(400.f, 300.f);
		player.entitySprite.setOrigin(player.entitySprite.getLocalBounds().width / 2.f, player.entitySprite.getLocalBounds().height / 2.f);
		player.setEntityType(1);
	}
	if (id == KeyList::ID::Enemy)
	{
		spawnEnemy();
	}
	if (id == KeyList::ID::Projectile)
	{
		
		projectile.entitySprite.setTexture(mTexture.getResource(KeyList::Projectile));
		projectile.setPosition(player.getPosition().x, (player.getPosition().y)-(player.entitySprite.getGlobalBounds().height));
		//aircraft.entitySprite.setOrigin(aircraft.entitySprite.getLocalBounds().width / 2.f, aircraft.entitySprite.getLocalBounds().height / 2.f);
		projectile.setEntityType(3);
		addEntity(projectile);
	}
}

void World::addEntity(Entity &entity)
{
	long ID = generateEntityID();
	entity.setEntityID(ID);
	entityList.push_back(entity);
}

void World::deleteEntity(long ID)
{
	if (ID != -1111)
	{
		std::vector<Entity>::iterator entityIndex;
		entityIndex = entityList.begin();
		while (entityIndex != entityList.end())
		{
			if ((*entityIndex).getEntityID() == ID)
			{
				entityList.erase(entityIndex);
				break;
			}
			entityIndex++;
		}
	}
}

long  World::generateEntityID()
{
	long ID=entityList.size()+1;
	while (1)
	{
		int result = searchEntity(ID);
		if (result == 2)
		{
			return ID;
		}
		if (result == 0)
		{
			return 1;
		}
		ID++;
	}
}

void World::generateBackground(KeyList::ID id)
{
	if (id == KeyList::ID::Space)
	{
		
		//sf::Texture texture = mTexture.getResource(KeyList::Space);
		//background.entitySprite.setTexture(texture);
		//texture.loadFromFile("A:/Pictures/Project/BackgroundForAsteroids.png");
		//texture.setRepeated(true);
		//texture.setSmooth(true);
		//background.entitySprite.setTexture(texture);
		background.entitySprite.setTexture(mTexture.getResource(KeyList::Space));
		background2.entitySprite.setTexture(mTexture.getResource(KeyList::Space));
		background.setPosition(0.f, 0.f);
		background2.setPosition(0.f, -768.f);
		//background.entitySprite.setTextureRect(sf::IntRect(0.f, 0.f, 1366.f, 768.f));
		//background2.entitySprite.setTextureRect(sf::IntRect(0.f, -768.f, 800.f, 600.f));
	}
}

void World::renderEntity(sf::RenderWindow &mWindow)
{
	long high = getHighestID();
	for (long id = 1; id <= high; id++)
	{
		checkForClearance(id);
	}
	std::vector<Entity>::iterator deleteIndex;
	deleteIndex = entityList.begin();
	while (deleteIndex != entityList.end())
	{
		checkForClearance((*deleteIndex).getEntityID());
		deleteIndex++;
	}
	std::vector<Entity>::iterator entityIndex;
	entityIndex = entityList.begin();
	while (entityIndex != entityList.end())
	{
		//drawEntitySprite(*entityIndex, mWindow);
		mWindow.draw(entityIndex->entitySprite);
		entityIndex++;
	}
	mWindow.draw(player.entitySprite);
}
int World::searchEntity(long ID)
{
	std::vector<Entity>::iterator entityIndex;
	if (entityList.size() != 0)
	{
		entityIndex = entityList.begin();
		while (entityIndex != entityList.end())
		{
			if ((*entityIndex).getEntityID() == ID)
			{
				return 1;
			}
			entityIndex++;
		}
		return 2;
	}
	return 0;
}

Entity& World::fetchEntity(long ID)
{
	std::vector<Entity>::iterator entityIndex;
	entityIndex = entityList.begin();
	while (entityIndex != entityList.end())
	{
		if ((*entityIndex).getEntityID() == ID)
		{
			return *entityIndex;
		}
		entityIndex++;
	}
	return Entity(-1111);
}

void World::drawEntitySprite(Entity entity, sf::RenderWindow &mWindow)
{
	mWindow.draw(entity.entitySprite);
}

void World::updateEntity(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (player.isMovingUp)
	{
		bool proceed=checkBorderCollision('y', '-');
		if (proceed)
		{
			movement.y -= 100.f;
		}
	}
	if (player.isMovingDown)
	{
		bool proceed = checkBorderCollision('y', '+');
		if (proceed)
		{
			movement.y += 100.f;
		}
	}
	if (player.isMovingLeft)
	{
		bool proceed = checkBorderCollision('x', '-');
		if (proceed)
		{
			movement.x -= 100.f;
		}
	}
	if (player.isMovingRight)
	{
		bool proceed = checkBorderCollision('x', '+');
		if (proceed)
		{
			movement.x += 100.f;
		}
	}
	if (player.isFiring)
	{
		if (player.getCanFire())
		{
			createEntity(KeyList::Projectile);
			player.setCanFire(false);
			player.setFiringUpdate(0.f);
		}
	}
	player.entitySprite.move(movement*deltaTime.asSeconds());
	player.setFiringUpdate(player.getFiringUpdate() + 0.8f*deltaTime.asSeconds());
	std::cout << player.getFiringUpdate() << std::endl;
	if (player.getFiringUpdate() >= player.getFiringRate())
	{
		player.setCanFire(true);
	}
	//player.entitySprite.setOrigin(player.entitySprite.getLocalBounds().width / 2.f, player.entitySprite.getLocalBounds().height / 2.f);
	//std::cout << "Player origin" << player.entitySprite.getOrigin().x << " " << player.entitySprite.getOrigin().y << std::endl;
	long entityLength = entityList.size();
	std::vector<long> IDList = checkEntityCollision();
	for (long var = 1; var <= IDList.size(); var++)
	{
		deleteEntity(var);
	}
	if (entityLength != 0)
	{
		long high = getHighestID();
		for (long id = 1; id <= high; id++)
		{
			updateEntityPosition(fetchEntity(id), deltaTime);
		}
	}
	if (entityLength == 0)
	{
		createEntity(KeyList::Enemy);
	}
}

void World::setEntityMovementStatus(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
	{
		player.isMovingUp = isPressed;
	}
	if (key == sf::Keyboard::S)
	{
		player.isMovingDown = isPressed;
	}
	if (key == sf::Keyboard::A)
	{
		player.isMovingLeft = isPressed;
	}
	if (key == sf::Keyboard::D)
	{
		player.isMovingRight = isPressed;
	}
	if (key == sf::Keyboard::Space)
	{
		player.isFiring = isPressed;
	}
}

void World::drawBackground(sf::RenderWindow &mWindow)
{
	mWindow.draw(background.entitySprite);
	mWindow.draw(background2.entitySprite);
}

unsigned int getCategory()
{
	return Category::Scene;
}

void World::updateEntityPosition(Entity& entity,sf::Time deltaTime)
{
	if (entity.getEntityID() != -1111)
	{
		sf::Vector2f movement(0.f, 0.f);
		if (entity.getEntityType() == 2)
		{
			movement.y += 20.f;
		}
		else if (entity.getEntityType() == 3)
		{
			movement.y -= 1000.f;
		}
		entity.entitySprite.move(movement*deltaTime.asSeconds());
		//entity.entitySprite.setOrigin(entity.entitySprite.getLocalBounds().width / 2.f, entity.entitySprite.getLocalBounds().height / 2.f);
		//std::cout << "Entity origin" << entity.entitySprite.getOrigin().x << " " << entity.entitySprite.getOrigin().y << std::endl;
	}
}

std::vector<long> World::checkEntityCollision()
{
	std::vector<Entity>::iterator entityIndex;
	std::vector<long> IDList;
	entityIndex = entityList.begin();
	while (entityIndex != entityList.end())
	{
		if (player.entitySprite.getGlobalBounds().intersects((*entityIndex).entitySprite.getGlobalBounds()))
		{
			IDList.push_back((*entityIndex).getEntityID());
		}
		std::vector<Entity>::iterator eIndex;
		eIndex = entityList.begin();
		while (eIndex != entityList.end())
		{
			if ((eIndex != entityIndex) && ((*entityIndex).entitySprite.getGlobalBounds().intersects((*eIndex).entitySprite.getGlobalBounds())))
			{
				IDList.push_back((*entityIndex).getEntityID());
				break;
			}
			eIndex++;
		}
		entityIndex++;
	}
	return IDList;
}

bool World::checkBorderCollision(char axis, char direction)
{
	sf::Vector2f position=player.entitySprite.getPosition();
	float leftEdge = position.x - ((player.entitySprite.getGlobalBounds()).width / 2);
	float rightEdge = position.x + ((player.entitySprite.getGlobalBounds()).width / 2);
	float topEdge = position.y - ((player.entitySprite.getGlobalBounds()).height / 2);
	float bottomEdge = position.y + ((player.entitySprite.getGlobalBounds()).height / 2);
	if (axis == 'x' && direction == '-')
	{
		if (leftEdge <= 0.f)
		{
			std::cout << "Inside" << std::endl;
			return false;
		}
	}
	else if (axis == 'x' && direction == '+')
	{
		if (rightEdge >= 800.f)
		{
			return false;
		}
	}
	else if (axis == 'y' && direction == '-')
	{
		if (topEdge <= 0.f)
		{
			return false;
		}
	}
	else if (axis == 'y' && direction == '+')
	{
		if (bottomEdge >= 600.f)
		{
			return false;
		}
	}
	return true;
}

void World::scrollBackground(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	movement.y += 20.f;
	if (player.isMovingUp)
	{
		movement.y += 40.f;
	}
	if (player.isMovingDown)
	{
		movement.y -= 10.f;
	}
	background.entitySprite.move(movement*deltaTime.asSeconds());
	background2.entitySprite.move(movement*deltaTime.asSeconds());
	if (background.getPosition().y >= 768.f)
	{
		background.setPosition(0.f, -768.f);
	}
	if (background2.getPosition().y >= 768)
	{
		background2.setPosition(0.f, -768.f);
	}
	//float bgy = background.entitySprite.getTextureRect().top;
	//std::cout << bgy << std::endl;
	//if (bgy > -600)
	//{
	//	std::cout << "Inside" << std::endl;
	//	bgy -= 10.f*deltaTime.asSeconds();
	//	std::cout << bgy << std::endl;
	//}
	//else
	//{
	//	bgy = 0;
	//}
	//background.entitySprite.setTextureRect(sf::IntRect(0.f, bgy, 1366.f, 768.f));
}

void World::checkForClearance(long ID)
{
	long deleteID=-1111;
	std::vector<Entity>::iterator entityIndex;
	entityIndex = entityList.begin();
	while (entityIndex != entityList.end())
	{
		if ((*entityIndex).getEntityID() == ID)
		{
			if ((*entityIndex).getPosition().x > 900 || (*entityIndex).getPosition().x < -100 || (*entityIndex).getPosition().y > 700 || (*entityIndex).getPosition().y < -100)
			{
				deleteID = (*entityIndex).getEntityID();
				break;
			}
		}
		entityIndex++;
	}
	deleteEntity(deleteID);
}

long World::getHighestID()
{
	long max = 0;
	std::vector<Entity>::iterator entityIndex;
	entityIndex = entityList.begin();
	while (entityIndex != entityList.end())
	{
		if ((*entityIndex).getEntityID() > max)
		{
			max=(*entityIndex).getEntityID();
		}
		entityIndex++;
	}
	return max;
}

void World::loadResources()
{
	mTexture.loadResource(KeyList::Player, "A:/Pictures/Project/spaceArt/png/player.png");
	mTexture.loadResource(KeyList::Enemy, "A:/Pictures/Project/spaceArt/png/enemyShip.png");
	mTexture.loadResource(KeyList::Projectile, "A:/Pictures/Project/spaceArt/png/laserRed.png");
	mTexture.loadResource(KeyList::Space, "A:/Pictures/Project/BackgroundForAsteroids.png");
}

void World::spawnEnemy()
{
	Aircraft aircraft;
	aircraft.entitySprite.setTexture(mTexture.getResource(KeyList::Enemy));
	aircraft.entitySprite.setOrigin(aircraft.entitySprite.getLocalBounds().width / 2.f, aircraft.entitySprite.getLocalBounds().height / 2.f);
	sf::Vector2f position = generateEnemyPosition();
	aircraft.setPosition(position);
	aircraft.setEntityType(2);
	addEntity(aircraft);
}

sf::Vector2f World::generateEnemyPosition()
{
	sf::Vector2f position(400.f, 0.f);
	return position;
}