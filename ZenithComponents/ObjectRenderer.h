#pragma once

#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>

namespace Zenith {
	using namespace Core;

	namespace Components {
		struct TransformComponent {
			glm::vec3 translation{};
			glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
			glm::vec3 rotation{};

			glm::mat4 mat4() { 
				const float c3 = glm::cos(rotation.z);
				const float s3 = glm::sin(rotation.z);
				const float c2 = glm::cos(rotation.x);
				const float s2 = glm::sin(rotation.x);
				const float c1 = glm::cos(rotation.y);
				const float s1 = glm::sin(rotation.y);
				return glm::mat4{
					{
						scale.x * (c1 * c3 + s1 * s2 * s3),
						scale.x * (c2 * s3),
						scale.x * (c1 * s2 * s3 - c3 * s1),
						0.0f,
					},
					{
						scale.y * (c3 * s1 * s2 - c1 * s3),
						scale.y * (c2 * c3),
						scale.y * (c1 * c3 * s2 + s1 * s3),
						0.0f,
					},
					{
						scale.z * (c2 * s1),
						scale.z * (-s2),
						scale.z * (c1 * c2),
						0.0f,
					},
					{translation.x, translation.y, translation.z, 1.0f} };
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
			TransformComponent transform{};

		private:
			ObjectRenderer(id_t rendId) : id{rendId} {}

			id_t id;
		};
	}
}