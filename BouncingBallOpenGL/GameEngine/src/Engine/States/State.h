#pragma once
#include <memory>

#ifdef EN_BUILD
#include "../Resources/ResourceManager.h"
#else
#include "../Resources/ResourceIdentifiers.h"
#endif

namespace En
{
	class Window;
	class Event;

	namespace States
	{ 
		class StateManager;

		class State
		{
		public:
			using StatePointer = std::unique_ptr<State>;

		public:
			struct Context
			{
				std::shared_ptr<Window> m_Window;
				std::shared_ptr<TextureManager> m_Textures;

				Context(std::shared_ptr<Window> window, std::shared_ptr<TextureManager> textures) 
					:	m_Window(std::move(window)),
						m_Textures(std::move(textures))
				{}
			};

		private:
			Context m_Context;
			StateManager* m_StateManager;

		protected:
			inline Context GetContext(void) const{	return m_Context; }

		public:
			State(StateManager& stateManager, Context context)
				:	m_StateManager(&stateManager),
					m_Context(context)
			{}
			virtual ~State(void) = default;

			virtual void OnRender(void) const = 0;
			virtual bool OnUpdate(double deltaTime) = 0;
			virtual bool OnEvent(Event& event) = 0;
		};

	}
}