
#include <iostream>
#include "hazel.h"

// This is how the client user creates their own application using Hazel
class Sandbox : public Hazel::Application {
public:
	Sandbox() { std::cout << "Sandbox ctor\n"; }
	~Sandbox(){}
};

// This is the entry point where Hazel runs the client application
Hazel::Application* Hazel::createApplication() {
	return new Sandbox;
}