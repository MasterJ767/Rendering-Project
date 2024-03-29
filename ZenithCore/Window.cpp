#include "Window.h"

#include <stdexcept>

using namespace Zenith::Core;

Window::Window(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
	initWindow();
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

VkExtent2D Window::getExtent() {
	return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
}

void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
	if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface");
	}
}

void Window::framebufferResizeCallback(GLFWwindow* glfwWindow, int width, int height) {
	auto window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
	window->framebufferResized = true;
	window->width = width;
	window->height = height;
}