#pragma once
#include "Window.h"

namespace Zenith {
	namespace Core {
		class App {
		public:
			static constexpr int WIDTH = 800;
			static constexpr int HEIGHT = 450;

			void run();
		private:
			Window window{ WIDTH, HEIGHT, "Hello Vulkan!" };
		};
	}
}