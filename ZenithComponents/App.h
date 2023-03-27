#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Model.h"
#include "GameObject.h"

#include <memory>
#include <vector>

namespace Zenith {
	using namespace Core;

	namespace Components {
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
			void loadGameObjects();

			Window window{ WIDTH, HEIGHT, "Hello Vulkan!" };
			Device device{ window };
			Renderer renderer{ window, device };

			std::vector<GameObject> gameObjects;
		};
	}
}