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

#include "ResourceManager.inl"

#include "../Graphics/Texture.h"
using TextureManager = ResourceManager<En::Texture, std::string>;

