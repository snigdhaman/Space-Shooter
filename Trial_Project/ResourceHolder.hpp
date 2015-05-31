#include<SFML\Graphics.hpp>
#include <memory>
#include "KeyList.h"
#ifndef __RESOURCE_HOLDER__
#define __RESOURCE_HOLDER__
template <typename Resource,typename Identifier>
class ResourceHolder
{
public:
	void loadResource (Identifier,const std::string&);
	Resource& getResource (Identifier);
private:
	std::map<KeyList::ID,std::unique_ptr<Resource>> mResourceMap;
};
#include "ResourceHolder.inl"
#endif