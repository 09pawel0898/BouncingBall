#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>


template <typename ResType, typename ResID>
class ResourceManager
{
private:
	std::unordered_map<ResID, std::shared_ptr<ResType>> m_Map;

private:
	void InsertResource(ResID resId, std::shared_ptr<ResType> res);

public:
	void LoadResource(ResID resId, const std::string& filename);
	std::shared_ptr<ResType>& GetResource(ResID resId);
	const std::shared_ptr<ResType>& GetResource(ResID resId) const;
};


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
	auto newResource = m_Map.insert(std::make_pair(id, std::move(resource)));
	assert(newResource.second);
}


#include "../Graphics/Texture.h"
using TextureManager = ResourceManager<En::Texture, std::string>;

