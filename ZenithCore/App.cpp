#include "App.h"

using namespace Zenith::Core;

void App::run() {
	while (window.shouldClose()) {
		glfwPollEvents();
	}
}