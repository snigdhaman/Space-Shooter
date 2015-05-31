#include <SFML\Graphics.hpp>
#include "ResourceHolder.hpp"
#include "KeyList.h"
#include "SceneNode.h"
#include "Entity.h"
#include "Aircraft.h"
#include "World.h"
#include "MusicPlayer.h"
#include <iostream>
#define timePerFrame sf::seconds(1.f/60.f)
#ifndef __GAME__
#define __GAME__
class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void update(sf::Time);
	void processEvents();
	void render();
	void handlePlayerInput(sf::Keyboard::Key, bool);

private:
	sf::RenderWindow mWindow;
	World mWorld;
	Aircraft eagle,raptor;
	sf::Sprite mSprite1;
	ResourceHolder<sf::Texture, KeyList::ID> mTexture;
	MusicPlayer music;
};
#endif