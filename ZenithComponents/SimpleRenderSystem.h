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
			SimpleRenderSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
			~SimpleRenderSystem();

			SimpleRenderSystem(const SimpleRenderSystem&) = delete;
			SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;
#
			void render(FrameInfo& frameInfo);

		private:
			void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
			void createPipeline(VkRenderPass renderPass);

			Device& device;

			std::unique_ptr<Pipeline> pipeline;
			VkPipelineLayout pipelineLayout;

			std::unique_ptr<DescriptorSetLayout> renderSystemLayout;
		};
	}
}