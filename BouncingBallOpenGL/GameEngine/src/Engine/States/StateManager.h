#pragma once

#include "State.h"
#include "../Core/Debug.h"

#include <functional>
#include <utility>
#include <cstdint>
#include <stack>
#include <map>

namespace En
{
	namespace States
	{
		class StateManager
		{
			using StateName = std::string;
			using StateConstructor = std::function<State::StatePointer(void)>;

		private:
			State::StatePointer CreateState(StateName stateName);
			void DoPendingActions(void);

		private:
			enum class Action : uint8_t	{ADD, DELETE} ;

			struct PendingAction
			{
				Action m_Action;
				StateName m_StateName;

				explicit PendingAction(Action action, StateName stateName = "NONE");
			};

		private:
			std::stack<State::StatePointer> m_States;
			std::map<StateName,StateConstructor> m_StateConstructors;
			std::vector<PendingAction> m_PendingActions;
			States::State::Context m_Context;

		public:
			explicit StateManager(State::Context context);

			template <typename StateType>
			inline void RegisterState(StateName stateName);

			void OnRender(void) const;
			void OnUpdate(double deltaTime);
			void OnEvent(Event& event);

			inline void PushState(StateName stateName);
			inline void PopState(void);
			bool IsEmpty(void) const;
		};

		template<typename StateType>
		inline void StateManager::RegisterState(StateName stateName)
		{
			EN_DEBUGMSG("%s%s%s", "[State] State '", stateName.c_str(), "' registered");
			m_StateConstructors[stateName] = [this](void)
			{
				return State::StatePointer(new StateType(*this, m_Context));
			};
		}

		inline void StateManager::PushState(StateName stateName)
		{
			EN_DEBUGMSG("%s%s%s", "[State] State '", stateName.c_str(), "' pushed");
			m_PendingActions.push_back(PendingAction(Action::ADD, stateName));
		}

		inline void StateManager::PopState(void)
		{
			EN_DEBUGMSG("%s", "[State] State popped from the top");
			m_PendingActions.push_back(PendingAction(Action::DELETE));
		}

		inline bool StateManager::IsEmpty(void) const
		{
			return m_States.empty();
		}
	}
}