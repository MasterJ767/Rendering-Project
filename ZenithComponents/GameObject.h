#pragma once

#include "Model.h"

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

		class GameObject {
		public:
			using id_t = unsigned int;
			using Map = std::unordered_map<id_t, GameObject>;

			static GameObject createGameObject() {
				static id_t currentId = 0;
				return GameObject{ currentId++ };
			}

			GameObject(const GameObject&) = delete;
			GameObject& operator=(const GameObject&) = delete;
			GameObject(GameObject&&) = default;
			GameObject& operator=(GameObject&&) = default;

			id_t getId() const { return id; }

			std::shared_ptr<Model> model{};
			glm::vec3 colour{};
			TransformComponent transform{};

		private:
			GameObject(id_t rendId) : id{rendId} {}

			id_t id;
		};
	}
}