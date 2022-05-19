
#include "hzpch.h"

#include "hazel.h"

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer() : Layer("Example"){}


	void onUpdate() override {
		//HZ_CLIENT_INFO("ExampleLayer::Update");
	}

	void onEvent(Hazel::Event& event) override {
		HZ_CLIENT_TRACE("{0}", event);
	}
};


// This is how the client user creates their own application using Hazel
class Sandbox : public Hazel::Application {
public:
	Sandbox() { 
		std::cout << "Sandbox ctor\n"; 
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImguiLayer());
	}
	~Sandbox(){}
};

// This is the entry point where Hazel runs the client application
Hazel::Application* Hazel::createApplication() {
	return new Sandbox;
}