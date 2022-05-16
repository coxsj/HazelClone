
#include <memory>
#include <iostream>
#include "hazel.h"

class Sandbox : public Hazel::Application {
public:
	Sandbox() { std::cout << "Sandbox ctor\n"; }
	~Sandbox(){}
};

Hazel::Application* Hazel::createApplication() {
	return new Sandbox;
}