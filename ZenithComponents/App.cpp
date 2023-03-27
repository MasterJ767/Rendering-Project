#include "App.h"
#include "Camera.h"
#include "Buffer.h"
#include "SimpleRenderSystem.h"
#include "PointLightSystem.h"
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
    globalPool = DescriptorPool::Builder(device)
        .setMaxSets(SwapChain::MAX_FRAMES_IN_FLIGHT)
        .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, SwapChain::MAX_FRAMES_IN_FLIGHT)
        .build();
	loadGameObjects();
}

App::~App() {
	
}

void App::run() {
    std::vector<std::unique_ptr<Buffer>> uboBuffers(SwapChain::MAX_FRAMES_IN_FLIGHT);
    for (int i = 0; i < uboBuffers.size(); ++i) {
        uboBuffers[i] = std::make_unique<Buffer>(device, sizeof(GlobalUbo), 1, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        uboBuffers[i]->map();
    }

    auto globalSetLayout = DescriptorSetLayout::Builder(device)
        .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
        .build();

    std::vector<VkDescriptorSet> globalDescriptorSets(SwapChain::MAX_FRAMES_IN_FLIGHT);
    for (int i = 0; i < globalDescriptorSets.size(); ++i) {
        auto bufferInfo = uboBuffers[i]->descriptorInfo();
        DescriptorWriter(*globalSetLayout, *globalPool)
            .writeBuffer(0, &bufferInfo)
            .build(globalDescriptorSets[i]);
    }

	SimpleRenderSystem simpleRenderSystem{ device, renderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout() };
    PointLightSystem pointLightSystem{ device, renderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout() };
    Camera camera{};

    auto viewerObject = GameObject::createGameObject();
    viewerObject.transform.translation.z = -2.5f;
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
        camera.setPerspectiveProjection(glm::radians(60.0f), aspect, 0.1f, 100.0f);
		
		if (auto commandBuffer = renderer.beginFrame()) {
            int frameIndex = renderer.getFrameIndex();
            FrameInfo frameInfo{ frameIndex, frameTime, commandBuffer, camera, globalDescriptorSets[frameIndex], gameObjects};

            GlobalUbo ubo{};
            ubo.projectionMatrix = camera.getProjection();
            ubo.viewMatrix = camera.getView();
            pointLightSystem.update(frameInfo, ubo);
            uboBuffers[frameIndex]->writeToBuffer(&ubo);
            uboBuffers[frameIndex]->flush();

			renderer.beginSwapChainRenderPass(commandBuffer);
			simpleRenderSystem.render(frameInfo);
            pointLightSystem.render(frameInfo);
			renderer.endSwapChainRenderPass(commandBuffer);
			renderer.endFrame();
		}
	}

	vkDeviceWaitIdle(device.device());
}

void App::loadGameObjects() {
    std::shared_ptr<Model> flatVaseModel = Model::createModelFromFile(device, "flat_vase.obj");
    std::shared_ptr<Model> smoothVaseModel = Model::createModelFromFile(device, "smooth_vase.obj");
    std::shared_ptr<Model> quadModel = Model::createModelFromFile(device, "quad.obj");

    auto gameObject = GameObject::createGameObject();
    gameObject.model = flatVaseModel;
    gameObject.transform.translation = { -1.0f, 0.5f, 0.0f };
    gameObject.transform.scale = glm::vec3(3.0f);
    gameObjects.emplace(gameObject.getId(), std::move(gameObject));

    auto gameObject2 = GameObject::createGameObject();
    gameObject2.model = smoothVaseModel;
    gameObject2.transform.translation = { 1.0f, 0.5f, 0.0f };
    gameObject2.transform.scale = glm::vec3(3.0f);
    gameObjects.emplace(gameObject2.getId(), std::move(gameObject2));

    auto gameObject3 = GameObject::createGameObject();
    gameObject3.model = quadModel;
    gameObject3.transform.translation = { 0.0f, 0.5f, 0.0f };
    gameObject3.transform.scale = glm::vec3(3.0f);
    gameObjects.emplace(gameObject3.getId(), std::move(gameObject3));

    std::vector<glm::vec3> lightColours{
      {1.f, .1f, .1f},
      {.1f, .1f, 1.f},
      {.1f, 1.f, .1f},
      {1.f, 1.f, .1f},
      {.1f, 1.f, 1.f},
      {1.f, 1.f, 1.f}
    };

    for (int i = 0; i < lightColours.size(); ++i) {
        auto pointLight = GameObject::makePointLight(0.2f);
        pointLight.colour = lightColours[i];
        auto rotateLight = glm::rotate(glm::mat4(1.0f), (i * glm::two_pi<float>()) / lightColours.size(), { 0.0f, -1.0f, 0.0f });
        pointLight.transform.translation = glm::vec3(rotateLight * glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f));
        gameObjects.emplace(pointLight.getId(), std::move(pointLight));
    }
}