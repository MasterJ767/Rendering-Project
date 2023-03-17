#pragma once
#include "Window.h"
#include "Pipeline.h"

namespace Zenith {
	namespace Core {
		class App {
		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 450;

			void run();
		private:
			Window window{ WIDTH, HEIGHT, "Hello Vulkan!" };
			Device device{ window };
			Pipeline pipeline{device,  "simple_shader.vert.spv", "simple_shader.frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
		};
	}
}