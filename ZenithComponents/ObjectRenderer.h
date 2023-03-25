#pragma once

#include "Model.h"

#include <memory>

namespace Zenith {
	using namespace Core;

	namespace Components {
		struct Transform2dComponent {
			glm::vec2 translation{};
			glm::vec2 scale{ 1.0f, 1.0f };
			float rotation;

			glm::mat2 mat2() { 
				const float s = glm::sin(rotation);
				const float c = glm::cos(rotation);
				glm::mat2 rotMatrix{ {c, s}, {-s, c} };
				glm::mat2 scaleMat{ {scale.x, 0.0f}, {0.0f, scale.y} };
				return rotMatrix * scaleMat; 
			}
		};

		class ObjectRenderer {
		public:
			using id_t = unsigned int;

			static ObjectRenderer createObjectRenderer() {
				static id_t currentId = 0;
				return ObjectRenderer{ currentId++ };
			}

			ObjectRenderer(const ObjectRenderer&) = delete;
			ObjectRenderer& operator=(const ObjectRenderer&) = delete;
			ObjectRenderer(ObjectRenderer&&) = default;
			ObjectRenderer& operator=(ObjectRenderer&&) = default;

			id_t getId() const { return id; }

			std::shared_ptr<Model> model{};
			glm::vec3 colour{};
			Transform2dComponent transform2d{};

		private:
			ObjectRenderer(id_t rendId) : id{rendId} {}

			id_t id;
		};
	}
}