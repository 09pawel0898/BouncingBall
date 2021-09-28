
template <typename ResType, typename ResID>
void ResourceManager<ResType, ResID>::LoadResource(ResID id, const std::string &filename)
{
	std::unique_ptr<ResType> resource(new ResType());

	//all resources classes(texture,font..) must provide loadFromFile() function
	
	if (resource->LoadFromFile(filename) == false)
		exit(EXIT_FAILURE);

	InsertResource(id, std::move(resource));
}

template <typename ResType, typename ResID>
ResType& ResourceManager<ResType, ResID>::GetResource(ResID id)
{
	auto foundResource = m_Map.find(id);
	assert(foundResource != m_Map.end());

	return *foundResource->second;
}

template <typename ResType, typename ResID>
const ResType& ResourceManager<ResType, ResID>::GetResource(ResID id) const
{
	auto foundResource = m_Map.find(id);
	assert(foundResource != m_Map.end());

	return *foundResource->second;
}

template <typename ResType, typename ResID>
void ResourceManager<ResType, ResID>::InsertResource(ResID id, std::unique_ptr<ResType> resource)
{
	auto newResource = m_Map.insert(std::make_pair(id, std::move(resource)));
	assert(newResource.second);
}
