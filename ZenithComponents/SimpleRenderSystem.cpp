#include "SimpleRenderSystem.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <stdexcept>
#include <array>

using namespace Zenith::Core;
using namespace Zenith::Components;

namespace Zenith {
	namespace Components {
		struct SimplePushConstantData {
			glm::mat4 modelMatrix{ 1.0f };
			glm::mat4 normalMatrix{ 1.0f };
		};
	}
}

SimpleRenderSystem::SimpleRenderSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) : device{ device } {
	createPipelineLayout(globalSetLayout);
	createPipeline(renderPass);
}

SimpleRenderSystem::~SimpleRenderSystem() {
	vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
}

void SimpleRenderSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {
	VkPushConstantRange pushConstantRange{};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	pushConstantRange.offset = 0;
	pushConstantRange.size = sizeof(SimplePushConstantData);

	renderSystemLayout = DescriptorSetLayout::Builder(device)
		.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT)
		.addBinding(1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT)
		.build();

	std::vector<VkDescriptorSetLayout> descriptorSetLayouts{
		globalSetLayout,
		renderSystemLayout->getDescriptorSetLayout() };

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = 1;
	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
	if (vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}
}

void SimpleRenderSystem::createPipeline(VkRenderPass renderPass) {
	assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

	PipelineConfigInfo pipelineConfig{};
	Pipeline::defaultPipelineConfigInfo(pipelineConfig);
	pipelineConfig.renderPass = renderPass;
	pipelineConfig.pipelineLayout = pipelineLayout;
	pipeline = std::make_unique<Pipeline>(device, "simple_shader.vert.spv", "simple_shader.frag.spv", pipelineConfig);
}

void SimpleRenderSystem::render(FrameInfo& frameInfo) {
	pipeline->bind(frameInfo.commandBuffer);

	vkCmdBindDescriptorSets(frameInfo.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, & frameInfo.globalDescriptorSet, 0, nullptr);

	for (auto& kv : frameInfo.gameObjects) {
		auto& obj = kv.second;
		if (obj.model == nullptr) { continue; }

		auto bufferInfo = obj.getBufferInfo(frameInfo.frameIndex);
		auto imageInfo = obj.diffuseMap->getImageInfo();
		VkDescriptorSet gameObjectDescriptorSet;
		DescriptorWriter(*renderSystemLayout, frameInfo.frameDescriptorPool)
			.writeBuffer(0, &bufferInfo)
			.writeImage(1, &imageInfo)
			.build(gameObjectDescriptorSet);

		vkCmdBindDescriptorSets(frameInfo.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 1, 1, &gameObjectDescriptorSet, 0, nullptr);

		SimplePushConstantData push{};
		auto modelMatrix = obj.transform.mat4();
		push.modelMatrix = modelMatrix;
		push.normalMatrix = obj.transform.normalMatrix();

		vkCmdPushConstants(frameInfo.commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(SimplePushConstantData), &push);
		obj.model->bind(frameInfo.commandBuffer);
		obj.model->draw(frameInfo.commandBuffer);
	}
}