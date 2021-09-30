#include "StateManager.h"
#include "../Events/Event.h"

#include <cassert>


namespace En
{
	namespace States
	{
		StateManager::StateManager(State::Context context) :
			m_States(),
			m_StateConstructors(),
			m_PendingActions(),
			m_Context(context)
		{}

		State::StatePointer StateManager::CreateState(StateName stateName)
		{
			auto stateConstructor = m_StateConstructors.find(stateName);
			assert(stateConstructor != m_StateConstructors.end());
			return stateConstructor->second();
		}

		void StateManager::DoPendingActions(void)
		{
			for (const auto& pendingAction : m_PendingActions)
			{
				if(pendingAction.m_Action == Action::ADD)
					m_States.push(CreateState(pendingAction.m_StateName));
				else if(pendingAction.m_Action == Action::DELETE)
					m_States.pop();
				m_States.top()->OnAwake();
			}
			m_PendingActions.clear();
		}

		void StateManager::OnRender(void) const
		{
			if(!IsEmpty())
				m_States.top()->OnRender();
		}

		void StateManager::OnUpdate(double deltaTime)
		{
			if (!IsEmpty())
				m_States.top()->OnUpdate(deltaTime);
			DoPendingActions();
		}

		void StateManager::OnEvent(Event& event)
		{
			if (!IsEmpty())
				m_States.top()->OnEvent(event);
			DoPendingActions();
		}

		
		StateManager::PendingAction::PendingAction(Action action, StateName stateName) 
		:	m_Action(action),
			m_StateName(stateName)
		{}
	}
}