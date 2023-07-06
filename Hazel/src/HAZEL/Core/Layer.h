#pragma once

#include"HAZEL/Core.h"
#include"HAZEL/Events/Event.h"

namespace Hazel {

	class HAZEL_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return mDebugName; }

	private:
		std::string mDebugName;
	};
}
