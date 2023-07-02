#include"hzpch.h"

#include"HAZEL/Core/Log.h"

#include"Platform/Windows/WindowsWindow.h"

namespace Hazel {
	
	static bool sGLFWInitialized = false;

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

			sGLFWInitialized = true;

		}

		mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(mWindow);
		glfwSetWindowUserPointer(mWindow, &mData);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		
		glfwDestroyWindow(mWindow);
	}

	void WindowsWindow::OnUpdate() {

		glfwPollEvents();
		glfwSwapBuffers(mWindow);
	}

	void WindowsWindow::SetVSync(bool enable) {

		if (enable) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		mData.VSync = enable;
	}

	bool WindowsWindow::IsVSync() const {

		return mData.VSync;
	}
}