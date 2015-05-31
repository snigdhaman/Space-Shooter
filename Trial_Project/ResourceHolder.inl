template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::loadResource (Identifier id,const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("Error while loading file:" + filename);
	}
	mResourceMap.insert(std::make_pair(id, std::move(resource)));
}

template<typename Resource,typename Identifier>
Resource& ResourceHolder<Resource,Identifier>::getResource(Identifier id)
{
	auto isFound = mResourceMap.find(id);
	return *isFound->second;
}