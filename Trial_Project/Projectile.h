#include "Entity.h"
#include <SFML\Graphics.hpp>
#ifndef __PROJECTILE__
#define __PROJECTILE__
class Projectile:public Entity
{
public:
	Projectile();
	~Projectile();
};
#endif