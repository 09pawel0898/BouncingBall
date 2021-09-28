#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>

template <typename ResType, typename ResID>
class ResourceManager
{
private:
	std::unordered_map<ResID, std::unique_ptr<ResType>> m_Map;

private:
	void InsertResource(ResID resId, std::unique_ptr<ResType> res);

public:
	void LoadResource(ResID resId, const std::string& filename);
	ResType& GetResource(ResID resId);
	const ResType& GetResource(ResID resId) const;
};

#include "ResourceManager.inl"

#ifdef EN_BUILD
#include "../Graphics/Texture.h"
using TextureManager = ResourceManager<Texture, std::string>;
#else
#include "ResourceIdentifiers.h"
#endif
