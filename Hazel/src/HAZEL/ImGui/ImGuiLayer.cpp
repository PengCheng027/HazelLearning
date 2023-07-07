#include"hzpch.h"

#include"HAZEL/ImGui/ImGuiLayer.h"
#include"HAZEL/Application.h"

#include"Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include<GLFW/glfw3.h>

namespace Hazel {

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer") {
		
	}
	
	ImGuiLayer::~ImGuiLayer() {
	
	}

	void ImGuiLayer::OnAttach() {

		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_BACKSPACE;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach() {

		
	}

	void ImGuiLayer::OnUpdate() {

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = mTime > 0.0f ? (time - mTime) : (1.0f / 60.0f);
		mTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {
	
	}
}