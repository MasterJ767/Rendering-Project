#pragma once

#include "Model.h"
#include "SwapChain.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <unordered_map>

namespace Zenith {
	using namespace Core;

	namespace Components {
		struct TransformComponent {
			glm::vec3 translation{};
			glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
			glm::vec3 rotation{};

			glm::mat4 mat4();
			glm::mat3 normalMatrix();
		};

		struct PointLightComponent {
			float lightIntensity = 1.0f;
		};

		struct GameObjectBufferData {
			glm::mat4 modelMatrix{ 1.0f };
			glm::mat4 normalMatrix{ 1.0f };
		};

		class GameObjectManager;

		class GameObject {
		public:
			using id_t = unsigned int;
			using Map = std::unordered_map<id_t, GameObject>;

			GameObject(GameObject&&) = default;
			GameObject(const GameObject&) = delete;
			GameObject& operator=(const GameObject&) = delete;
			GameObject& operator=(GameObject&&) = default;

			id_t getId() const { return id; }

			VkDescriptorBufferInfo getBufferInfo(int frameIndex);

			glm::vec3 colour{};
			TransformComponent transform{};

			std::shared_ptr<Model> model{};
			std::shared_ptr<Texture> diffuseMap = nullptr;
			std::unique_ptr<PointLightComponent> pointLight = nullptr;

		private:
			GameObject(id_t rendId, const GameObjectManager& manager);

			id_t id;
			const GameObjectManager& gameObjectManager;

			friend class GameObjectManager;
		};

		class GameObjectManager {
		public:
			static constexpr int MAX_GAME_OBJECTS = 1000;

			GameObjectManager(Device& device);
			GameObjectManager(const GameObjectManager&) = delete;
			GameObjectManager& operator=(const GameObjectManager&) = delete;
			GameObjectManager(GameObjectManager&&) = delete;
			GameObjectManager& operator=(GameObjectManager&&) = delete;

			GameObject& createGameObject() {
				assert(currentId < MAX_GAME_OBJECTS && "Max game object count exceeded!");
				auto gameObject = GameObject{ currentId++, *this };
				auto gameObjectId = gameObject.getId();
				gameObject.diffuseMap = textureDefault;
				gameObjects.emplace(gameObjectId, std::move(gameObject));
				return gameObjects.at(gameObjectId);
			}

			GameObject& makePointLight(float intensity = 10.f, float radius = 0.1f, glm::vec3 color = glm::vec3(1.f));

			VkDescriptorBufferInfo getBufferInfoForGameObject(int frameIndex, GameObject::id_t gameObjectId) const {
				return uboBuffers[frameIndex]->descriptorInfoForIndex(gameObjectId);
			}

			void updateBuffer(int frameIndex);

			GameObject::Map gameObjects{};
			std::vector<std::unique_ptr<Buffer>> uboBuffers{ SwapChain::MAX_FRAMES_IN_FLIGHT };

		private:
			GameObject::id_t currentId = 0;
			std::shared_ptr<Texture> textureDefault;
		};
	}
}