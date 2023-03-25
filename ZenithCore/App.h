#pragma once
#include "Window.h"
#include "Pipeline.h"
#include "SwapChain.h"
#include "Model.h"
#include "ObjectRenderer.h"

#include <memory>
#include <vector>

namespace Zenith {
	namespace Core {
		class App {
		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 450;

			App();
			~App();

			App(const App&) = delete;
			App& operator=(const App&) = delete;

			void run();
		private:
			void loadObjectRenderers();
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void freeCommandBuffers();
			void drawFrame();
			void recreateSwapChain();
			void recordCommandBuffer(int imageIndex);
			void renderObjectRenderers(VkCommandBuffer commandBuffer);

			Window window{ WIDTH, HEIGHT, "Hello Vulkan!" };
			Device device{ window };
			std::unique_ptr<SwapChain> swapChain;
			std::unique_ptr<Pipeline> pipeline;
			VkPipelineLayout pipelineLayout;
			std::vector<VkCommandBuffer> commandBuffers;
			std::vector<ObjectRenderer> objectRenderers;
		};
	}
}