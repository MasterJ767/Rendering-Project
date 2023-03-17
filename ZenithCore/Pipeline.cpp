#include "Pipeline.h"
#include "Assets.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace Zenith::Core;

Pipeline::Pipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
	createGraphicsPipeline(Util::SHADERDIR + vertFilepath, Util::SHADERDIR + fragFilepath);
}

std::vector<char> Pipeline::readFile(const std::string& filepath) {
	std::ifstream file(filepath, std::ios::ate | std::ios::binary);
	if (!file.is_open()) {
		throw std::runtime_error("failed to open file : " + filepath);
	}
	size_t fileSize = static_cast<size_t>(file.tellg());
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	return buffer;
}

void Pipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
	std::vector<char> vertCode = readFile(vertFilepath);
	std::vector<char> fragCode = readFile(fragFilepath);

	std::cout << "Vertex Shader Code Size: " << vertCode.size() << "\n";
	std::cout << "Fragment Shader Code Size: " << fragCode.size() << "\n";
}