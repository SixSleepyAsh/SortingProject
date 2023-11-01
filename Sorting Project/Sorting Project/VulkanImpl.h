#pragma once
#include <vector>
#include <vulkan/vulkan.hpp>
#include <glfw/glfw3.h>

namespace VKImpl
{
	vk::UniqueInstance createVulkanInstance(const char** instance_extensions,
	                          unsigned extension_count,
		vk::ApplicationInfo app_info = {
			{},{},{},{},vk::ApiVersion13
		});

	std::pair<vk::PhysicalDevice, size_t> SelectVulkanDevice(vk::Instance& instance);

	vk::UniqueDevice createLogicalDevice(const vk::UniqueInstance& instance, vk::PhysicalDevice physical_device, size_t selected_queue);

	vk::SurfaceFormatKHR selectFormat(vk::PhysicalDevice& physDevice, vk::SurfaceKHR& surface);

	vk::UniqueSwapchainKHR createSwapchain(vk::Device& device, vk::PhysicalDevice& physDeivce, vk::SurfaceKHR& surface, GLFWwindow* window, vk::SurfaceFormatKHR
	                                               surfaceFormat, vk::SwapchainKHR oldSwapchain = {});
	std::vector<vk::UniqueImageView> defaultImageViews(vk::Device& device, vk::SwapchainKHR& swapchain, vk::Format surfaceFormat);
}
