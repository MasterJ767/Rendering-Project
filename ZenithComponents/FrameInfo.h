#pragma once

#include "Camera.h"
#include "GameObject.h"

#include <vulkan/vulkan.h>

namespace Zenith {
	namespace Components {
#define MAX_LIGHTS 10

		struct PointLight {
			glm::vec4 position{};
			glm::vec4 colour{};
		};

		struct GlobalUbo {
			glm::mat4 projectionMatrix{ 1.0f };
			glm::mat4 viewMatrix{ 1.0f };
			glm::mat4 inverseViewMatrix{ 1.0f };
			glm::vec4 ambientLightColour{ 1.0f, 1.0f, 1.0f, 0.02f };
			PointLight pointLights[MAX_LIGHTS];
			int numLights;
		};

		struct FrameInfo {
			int frameIndex;
			float frameTime;
			VkCommandBuffer commandBuffer;
			Camera& camera;
			VkDescriptorSet globalDescriptorSet;
			GameObject::Map& gameObjects;
		};
	}
}