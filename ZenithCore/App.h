#pragma once
#include "Window.h"
#include "Pipeline.h"
#include "SwapChain.h"

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
			void createPipelineLayout();
			void createPipeline();
			void createCommandBuffers();
			void drawFrame();

			Window window{ WIDTH, HEIGHT, "Hello Vulkan!" };
			Device device{ window };
			SwapChain swapChain{ device, window.getExtent() };
			std::unique_ptr<Pipeline> pipeline;
			VkPipelineLayout pipelineLayout;
			std::vector<VkCommandBuffer> commandBuffers;
		};
	}
}