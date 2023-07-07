#include"hzpch.h"

#include"HAZEL/Core/Log.h"

#include"HAZEL/Events/ApplicationEvent.h"
#include"HAZEL/Events/KeyEvent.h"
#include"HAZEL/Events/MouseEvent.h"

#include"Platform/Windows/WindowsWindow.h"

#include<glad/glad.h>

namespace Hazel {
	
	static bool sGLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {

		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) {

		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {

		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		
		glfwDestroyWindow(mWindow);
	}

	void WindowsWindow::Init(const WindowProps& props) {

		mData.Width = props.Width;
		mData.Height = props.Height;
		mData.Title = props.Title;

		HZ_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

		if (!sGLFWInitialized) {

			// TODD: glfwTerminate on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Cloud not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);

			sGLFWInitialized = true;

		}

		mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), 
			nullptr, nullptr); // this function will create a window pointer and context

		glfwMakeContextCurrent(mWindow); // this function make the window in current context
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Faild to initialize Glad!");
		glfwSetWindowUserPointer(mWindow, &mData); // set some information of window to use later
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height){
			// get the information about this window
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			//	using this function point, call Event.this funtion point binded by 
			//	Window::SetEventCallback(const EventCallbackFn& callback)
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch(action) {

				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int	action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {

				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window,double xPos,double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown() {
		
		glfwDestroyWindow(mWindow);
	}

	void WindowsWindow::OnUpdate() {
		// this function will process events in queue
		glfwPollEvents();

		glfwSwapBuffers(mWindow);
	}

	void WindowsWindow::SetVSync(bool enable) {

		if (enable) {
			// wait for SwapBuffer is ready to swap
			glfwSwapInterval(1);
		}
		else {
			// Swap buffer immediately, event the buffer is'n ready
			glfwSwapInterval(0);
		}

		mData.VSync = enable;
	}

	bool WindowsWindow::IsVSync() const {

		return mData.VSync;
	}
}