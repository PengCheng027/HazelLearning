#include"hzpch.h"

#include "Application.h"

#include"HAZEL/Events/ApplicationEvent.h"

#include<glad/glad.h>

namespace Hazel {

	#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application* Application::sInstance = nullptr;

	Application::Application() {

		HZ_CORE_ASSERT(!sInstance, "Application already exists");
		sInstance = this;

		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application:: ~Application() {
	}

	void Application::PunshLayer(Layer* layer) {

		mLayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PunshOverlay(Layer* layer) {

		mLayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	// WindowsWindow's mData.EventCallback bind this function
	void Application::OnEvent(Event& e) {

		EventDispatcher dispathche(e);
		// make sure the event is'n WindowCloseEvent
		dispathche.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

		for (auto it = mLayerStack.end(); it != mLayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {

		while (mRunning) {
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : mLayerStack)
				layer->OnUpdate();

			mWindow->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e) {
		
		mRunning = false;
		return true;
	}

}
