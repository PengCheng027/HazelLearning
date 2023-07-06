#pragma once

#include "Core.h"
#include"HAZEL/Core/Window.h"
#include"HAZEL/Core/LayerStack.h"
#include"HAZEL/Events/ApplicationEvent.h"

namespace Hazel {

	class HAZEL_API Application{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		void PunshLayer(Layer* layer);
		void PunshOverlay(Layer* layer);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> mWindow;
		bool mRunning = true;
		LayerStack mLayerStack;
	};

	Application* CreateApplication();
}

