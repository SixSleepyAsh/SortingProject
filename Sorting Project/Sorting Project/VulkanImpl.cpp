#include "VulkanImpl.h"
#include "vulkan/vulkan.hpp"
#include <glfw/glfw3.h>

vk::UniqueInstance VKImpl::createVulkanInstance(
	const char** instance_extensions, 
	unsigned extension_count,
	vk::ApplicationInfo app_info)
{
	vk::InstanceCreateInfo instance_info
	{
		{},
		&app_info,
		0,
		nullptr,
		extension_count,
		instance_extensions
	};

	return std::move(vk::createInstanceUnique(instance_info));
}

#define DEFAULT_DEVICE_INDEX 0

std::pair<vk::PhysicalDevice, size_t> VKImpl::SelectVulkanDevice(vk::Instance& instance)
{
	unsigned count;
	instance.enumeratePhysicalDevices(&count, nullptr);
	std::vector<vk::PhysicalDevice> device_properties;
	instance.enumeratePhysicalDevices(&count, &device_properties[0]);

	if (device_properties.size() <= 0)
		throw std::runtime_error("No vulkan devices available!");

	// TODO: better device selection

	std::vector<vk::QueueFamilyProperties>  family_properties = 
		device_properties[DEFAULT_DEVICE_INDEX].getQueueFamilyProperties();

	vk::PhysicalDevice device;
	int i = 0;
	auto family_it = family_properties.begin();
	while(family_it != family_properties.end())
	{
		if (glfwGetPhysicalDevicePresentationSupport(instance,
			device_properties[DEFAULT_DEVICE_INDEX], i) &&
			family_it->queueFlags & vk::QueueFlagBits::eGraphics)
		{
			
		}

		i++;
	}


	return { device_properties[0], i };
}

vk::UniqueDevice VKImpl::createLogicalDevice(const vk::UniqueInstance& instance, vk::PhysicalDevice physical_device,
	size_t selected_queue)
{
	float one = 1;
	vk::DeviceQueueCreateInfo queue_info
	{
		{},
		static_cast<unsigned>(selected_queue),
		1,
		&one
	};

	constexpr const char* REQUIRED_EXTENSIONS[] = { "VK_KHR_swapchain" };

	vk::DeviceCreateInfo device_info
	{
		{},
		1,
		&queue_info,
		0,
		{},
		_countof(REQUIRED_EXTENSIONS),
		REQUIRED_EXTENSIONS
	};

	return std::move(physical_device.createDeviceUnique(device_info));
}
