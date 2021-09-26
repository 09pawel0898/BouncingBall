#pragma once

namespace En
{
	class Event;

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach(void) {}
		virtual void OnDetach(void) {}
		virtual void OnEvent(void)	{}
		virtual void OnUpdate(void)	{}
		virtual void OnEvent(Event& event)	{}
	};
}