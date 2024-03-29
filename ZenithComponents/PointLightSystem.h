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
		class PointLightSystem {
		public:
			PointLightSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
			~PointLightSystem();

			PointLightSystem(const PointLightSystem&) = delete;
			PointLightSystem& operator=(const PointLightSystem&) = delete;
#
			void update(FrameInfo& frameInfo, GlobalUbo& ubo);
			void render(FrameInfo& frameInfo);

		private:
			void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
			void createPipeline(VkRenderPass renderPass);

			Device& device;

			std::unique_ptr<Pipeline> pipeline;
			VkPipelineLayout pipelineLayout;
		};
	}
}