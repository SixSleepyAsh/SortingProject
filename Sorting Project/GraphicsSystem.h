#pragma once
#include "System.h"
#include <vulkan/vulkan.hpp>
#include <glfw/glfw3.h>


class GraphicsSystem : public System
{
	vk::UniqueInstance m_instance{};
	vk::PhysicalDevice m_physDevice{};
	GLFWwindow* m_window{};
	size_t m_selectedQueue{};
	vk::UniqueDevice m_logicalDevice{};
	vk::Queue m_queue;
	vk::UniqueSurfaceKHR m_surface;
	vk::SurfaceFormatKHR m_surfaceFormat;
	vk::UniqueSwapchainKHR m_swapchain;
	std::vector<vk::UniqueImageView> m_imageViews;
	vk::UniqueDescriptorPool m_descriptorPool{};
	vk::CommandBuffer m_commandBuffer{};
	vk::UniqueRenderPass m_renderPass{};
	uint32_t m_imageCount{};

	GraphicsSystem() : System("Graphics System") {}

public:
	
	vk::Instance GetVulkanInstance() const { return m_instance.get(); }
	vk::PhysicalDevice GetPhysicalDevice() const { return m_physDevice; }
	vk::Device GetLogicalDevice() const { return m_logicalDevice.get(); }
	vk::Queue GetQueue() const { return m_queue; }
	uint32_t GetQueueFamilyIndex() const { return m_selectedQueue; }
	vk::DescriptorPool GetDescriptorPool() const { return m_descriptorPool.get(); }
	vk::CommandBuffer GetCommandBuffer() const { return m_commandBuffer; } 
	vk::RenderPass GetRenderPass() const { return m_renderPass.get(); }
	uint32_t GetImageCount() const { return m_imageCount; }


public:

	static GraphicsSystem* GetInstance();

	GLFWwindow* getWindow();;

	void OnInit() override;
	void OnFixedUpdate() override;
	void OnUpdate(float dt) override;
	void OnExit() override;;
};

__inline GraphicsSystem* Graphics() { return GraphicsSystem::GetInstance(); }
