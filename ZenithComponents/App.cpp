#include "App.h"
#include "SimpleRenderSystem.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <stdexcept>
#include <array>

using namespace Zenith::Core;
using namespace Zenith::Components;

App::App() {
	loadObjectRenderers();
}

App::~App() {
	
}

void App::run() {
	SimpleRenderSystem simpleRenderSystem{ device, renderer.getSwapChainRenderPass() };

	while (!window.shouldClose()) {
		glfwPollEvents();
		
		if (auto commandBuffer = renderer.beginFrame()) {
			renderer.beginSwapChainRenderPass(commandBuffer);
			simpleRenderSystem.renderObjectRenderers(commandBuffer, objectRenderers);
			renderer.endSwapChainRenderPass(commandBuffer);
			renderer.endFrame();
		}
	}

	vkDeviceWaitIdle(device.device());
}

void App::loadObjectRenderers() {
	std::vector<Model::Vertex> vertices{
		{ {0.0f, -0.5f}, {1.0f, 0.0f, 0.0f} },
		{ {0.5f, 0.5f}, {0.0f, 1.0f, 0.0f} },
		{ {-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f} }
	};

	auto model = std::make_shared<Model>(device, vertices);

	auto triangle = ObjectRenderer::createObjectRenderer();
	triangle.model = model;
	triangle.colour = { 0.1f, 0.8f, 0.1f };
	triangle.transform2d.translation.x = 0.2f;
	triangle.transform2d.scale = { 2.0f, 0.5f };
	triangle.transform2d.rotation = 0.25f * glm::two_pi<float>();

	objectRenderers.push_back(std::move(triangle));
}