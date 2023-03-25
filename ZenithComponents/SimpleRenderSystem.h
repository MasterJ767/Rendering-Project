#pragma once
#include "Camera.h"
#include "Pipeline.h"
#include "Model.h"
#include "ObjectRenderer.h"

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
			void renderObjectRenderers(VkCommandBuffer commandBuffer, std::vector<ObjectRenderer>& objectRenderers, const Camera& camera);

		private:
			void createPipelineLayout();
			void createPipeline(VkRenderPass renderPass);

			Device& device;

			std::unique_ptr<Pipeline> pipeline;
			VkPipelineLayout pipelineLayout;
		};
	}
}