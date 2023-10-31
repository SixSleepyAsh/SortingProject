#pragma once
#include <vector>
#include "vulkan/vulkan.hpp"

namespace VKImpl
{
	vk::UniqueInstance createVulkanInstance(const char** instance_extensions,
	                          unsigned extension_count,
		vk::ApplicationInfo app_info = {
			{},{},{},{},vk::ApiVersion13
		});

	std::pair<vk::PhysicalDevice, size_t> SelectVulkanDevice(vk::Instance& instance);

	vk::UniqueDevice createLogicalDevice(const vk::UniqueInstance& instance, vk::PhysicalDevice physical_device, size_t selected_queue);
}
