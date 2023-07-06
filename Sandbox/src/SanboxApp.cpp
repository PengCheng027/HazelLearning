#include<Hazel.h>

class ExampleLayer :public Hazel::Layer {
public:
	ExampleLayer()
		:Layer("Example") {

	}

	void OnUpdate() override{
		
		HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) override {

		HZ_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		// push a layer into Layer container, it always be there
		// until be destroyed
		PunshLayer(new ExampleLayer());
	}

	~Sandbox() {
	
	}
};

Hazel::Application* Hazel::CreateApplication() {

	return new Sandbox();
}