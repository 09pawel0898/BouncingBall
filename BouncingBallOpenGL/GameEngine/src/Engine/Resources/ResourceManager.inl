#include "../Core/Debug.h"

template <typename ResType, typename ResID>
void ResourceManager<ResType, ResID>::LoadResource(ResID id, const std::string& filename)
{
	std::shared_ptr<ResType> resource(new ResType());

	//all resources classes(texture,font..) must provide LoadFromFile() function

	if (resource->LoadFromFile(filename) == false)
		exit(EXIT_FAILURE);

	InsertResource(id, std::move(resource));
}

template <typename ResType, typename ResID>
std::shared_ptr<ResType>& ResourceManager<ResType, ResID>::GetResource(ResID id)
{
	auto foundResource = m_Map.find(id);
	assert(foundResource != m_Map.end());

	return foundResource->second;
}

template <typename ResType, typename ResID>
const std::shared_ptr<ResType>& ResourceManager<ResType, ResID>::GetResource(ResID id) const
{
	auto foundResource = m_Map.find(id);
	assert(foundResource != m_Map.end());

	return foundResource->second;
}

template <typename ResType, typename ResID>
void ResourceManager<ResType, ResID>::InsertResource(ResID id, std::shared_ptr<ResType> resource)
{
	if (m_Map.find(id) != m_Map.end())
	{
		EN_DEBUGMSG("%s", "[Resource] Attempting to add a resource that is already owned");
		return;
	}
	auto newResource = m_Map.insert(std::make_pair(id, std::move(resource)));
	assert(newResource.second);
}