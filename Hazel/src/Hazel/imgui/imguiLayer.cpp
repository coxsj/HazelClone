#include "hzpch.h"
#include "Hazel/imgui/imguiLayer.h"
#include "imgui.h"
#include "platform/OpenGL/imguiOpenGLRenderer.h"
#include "Hazel/application.h"
#include "Hazel/core.h"
#include "Hazel/events/mouseEvent.h"

//HACK should not be including GLFW here
#include "GLFW/glfw3.h" 
#include "glad/glad.h"

namespace Hazel {

	void ImguiLayer::onAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TODO TEMPORARY: should eventually use Hazel key codes
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
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImguiLayer::onDetach()	{

	}

	void ImguiLayer::onUpdate()	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.getWindow().GetWidth(), app.getWindow().GetHeight());

		float time = static_cast<float>(glfwGetTime());
		io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiLayer::onEvent(Event& event)	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseButtonPressedEvent>(HZ_BIND_EVENT_FN(ImguiLayer::OnMouseButtonPressedEvent));
		dispatcher.dispatch<MouseButtonReleasedEvent>(HZ_BIND_EVENT_FN(ImguiLayer::OnMouseButtonReleasedEvent));
		dispatcher.dispatch<MouseMovedEvent>(HZ_BIND_EVENT_FN(ImguiLayer::OnMouseMovedEvent));
		dispatcher.dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(ImguiLayer::OnMouseScrolledEvent));
		dispatcher.dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FN(ImguiLayer::OnKeyPressedEvent));
		dispatcher.dispatch<KeyTypedEvent>(HZ_BIND_EVENT_FN(ImguiLayer::OnKeyTypedEvent));
		dispatcher.dispatch<KeyReleasedEvent>(HZ_BIND_EVENT_FN(ImguiLayer::OnKeyReleasedEvent));
		dispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(ImguiLayer::OnWindowResizeEvent));
	}

	bool ImguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		//since ImguiLayer is not handling this event, we return false
		return false;
	}

	bool ImguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImguiLayer::OnMouseMovedEvent(MouseMovedEvent& e)	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.getX(), e.getY());

		return false;
	}

	bool ImguiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.getXOffset();
		io.MouseWheel   += e.getYOffset();

		return false;
	}

	bool ImguiLayer::OnKeyPressedEvent(KeyPressedEvent& e)	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]       || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT]              || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]  || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImguiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImguiLayer::OnKeyTypedEvent(KeyTypedEvent& e)	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);
		
		return false;
	}


	bool ImguiLayer::OnWindowResizeEvent(WindowResizeEvent& e)	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight()); 
		return false;
	}

}