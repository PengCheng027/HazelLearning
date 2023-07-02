#pragma once

#include "Core.h"
#include"HAZEL/Core/Window.h"

namespace Hazel {

	class HAZEL_API Application{

	public:
		Application();
		virtual ~Application();
		void Run();

	private:
		std::unique_ptr<Window> mWindow;
		bool mRunning = true;
	};

	Application* CreateApplication();
}

