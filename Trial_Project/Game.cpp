#include "Game.h"


Game::Game() :mWindow(sf::VideoMode(800.f, 600.f), "You damn better run"), mTexture(), mWorld(mWindow)
{
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdated = sf::Time::Zero;
	mWorld.loadResources();
	mWorld.generateBackground(KeyList::Space);
	mWorld.createEntity(KeyList::Enemy);
	mWorld.createEntity(KeyList::Player);
	mWindow.display();
	music.play(Music::MissionTheme);
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdated += clock.restart();
		if (timeSinceLastUpdated > timePerFrame)
		{
			processEvents();
			timeSinceLastUpdated -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}


void Game::update(sf::Time deltaTime)
{
	mWorld.updateEntity(deltaTime);
	mWorld.scrollBackground(deltaTime);
}


void Game::render()
{
	mWindow.clear();
	mWorld.drawBackground(mWindow);
	mWorld.renderEntity(mWindow);
	mWindow.display();
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	mWorld.setEntityMovementStatus(key,isPressed);
}