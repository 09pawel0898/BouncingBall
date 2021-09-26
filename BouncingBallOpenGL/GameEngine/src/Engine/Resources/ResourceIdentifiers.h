#pragma once

#include <string>

namespace En
{
	template <typename ResType, typename ResID>
	class ResourceManager;

	namespace States
	{
		class StateManager;
	}
}

class Texture;
using TextureManager = En::ResourceManager<Texture, std::string>;