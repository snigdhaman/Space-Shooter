#include <functional>
#include <SFML\Graphics.hpp>
#include "World.h"
#ifndef __COMMAND__
#define __COMMAND__
class Command
{
public:
	Command();
	~Command();
	std::function <void(World&,sf::Time)> action;
};
#endif