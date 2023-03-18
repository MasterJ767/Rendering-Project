#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace Zenith {
	namespace Core {
		class Window {
		public:
			Window(int w, int h, std::string name);
			~Window();

			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

			bool shouldClose();
			VkExtent2D getExtent();

			void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
		private:
			void initWindow();

			const int width;
			const int height;

			std::string windowName;
			GLFWwindow* window;
		};
	}
}