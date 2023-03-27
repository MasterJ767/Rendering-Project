#pragma once
#include "Camera.h"
#include "Pipeline.h"
#include "Model.h"
#include "GameObject.h"
#include "FrameInfo.h"

#include <memory>
#include <vector>

namespace Zenith {
	using namespace Core;

	namespace Components {
		class SimpleRenderSystem {
		public:
			SimpleRenderSystem(Device& device, VkRenderPass renderPass);
			~SimpleRenderSystem();

			SimpleRenderSystem(const SimpleRenderSystem&) = delete;
			SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;
#
			void renderGameObjects(FrameInfo& frameInfo, std::vector<GameObject>& gameObjects);

		private:
			void createPipelineLayout();
			void createPipeline(VkRenderPass renderPass);

			Device& device;

			std::unique_ptr<Pipeline> pipeline;
			VkPipelineLayout pipelineLayout;
		};
	}
}