#include "App.h"
#include "Camera.h"
#include "SimpleRenderSystem.h"
#include "KeyboardMovement.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <stdexcept>
#include <array>
#include <chrono>

using namespace Zenith::Core;
using namespace Zenith::Components;
using namespace Zenith::Logic;

App::App() {
	loadGameObjects();
}

App::~App() {
	
}

void App::run() {
	SimpleRenderSystem simpleRenderSystem{ device, renderer.getSwapChainRenderPass() };
    Camera camera{};
    //camera.setViewDirection(glm::vec3(0.0f), glm::vec3(0.5f, 0.0f, 1.0f));
    camera.setViewTarget(glm::vec3(-1.0f, -2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 2.5f));

    auto viewerObject = GameObject::createGameObject();
    KeyboardMovement cameraController{};

    auto currentTime = std::chrono::high_resolution_clock::now();

	while (!window.shouldClose()) {
		glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        cameraController.moveInPlaneXZ(window.getGLFWWindow(), frameTime, viewerObject);
        camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

        float aspect = renderer.getAspectRatio();
        camera.setPerspectiveProjection(glm::radians(60.0f), aspect, 0.1f, 10.0f);
		
		if (auto commandBuffer = renderer.beginFrame()) {
			renderer.beginSwapChainRenderPass(commandBuffer);
			simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
			renderer.endSwapChainRenderPass(commandBuffer);
			renderer.endFrame();
		}
	}

	vkDeviceWaitIdle(device.device());
}

void App::loadGameObjects() {
    std::shared_ptr<Model> model = Model::createModelFromFile(device, "flat_vase.obj");

    auto gameObject = GameObject::createGameObject();
    gameObject.model = model;
    gameObject.transform.translation = { 0.0f, 0.5f, 2.5f };
    gameObject.transform.scale = glm::vec3(3.0f);
    gameObjects.push_back(std::move(gameObject));
}