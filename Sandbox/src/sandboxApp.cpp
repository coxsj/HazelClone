
#include "hzpch.h"

#include "hazel.h"
#include "imgui/imgui.h"

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer() : Layer("Example"){}


	void onUpdate() override {
		//Once per frame
		//HZ_CLIENT_INFO("ExampleLayer::Update");
		if (Hazel::Input::isKeyPressed(HZ_KEY_TAB)) {
			HZ_CLIENT_INFO("Tab key pressed!");
		}
	}

	virtual void onImGuiRender() override {
		//ImGui::Begin("Test");
		//ImGui::Text("Hello world");
		//ImGui::End();
	}

	void onEvent(Hazel::Event& event) override {
		//As events happen, callbacks generate events which propagate to the application
		//HZ_CLIENT_TRACE("{0}", event);

		if (event.GetEventType() == Hazel::EventType::kKeyPressed) {
			Hazel::KeyPressedEvent& e = static_cast<Hazel::KeyPressedEvent& >(event);
			HZ_CLIENT_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
		}
	}
};


// This is how the client user creates their own application using Hazel
class Sandbox : public Hazel::Application {
public:
	Sandbox() { 
		std::cout << "Sandbox ctor\n"; 
		PushLayer(new ExampleLayer());
	}
	~Sandbox(){}
};

// This is the entry point where Hazel runs the client application
Hazel::Application* Hazel::createApplication() {
	return new Sandbox;
}