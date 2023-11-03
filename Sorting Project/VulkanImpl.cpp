#include "VulkanImpl.h"
#include <vulkan/vulkan.hpp>
#include <glfw/glfw3.h>
#include <glm/vec2.hpp>

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
	std::vector<vk::PhysicalDevice> device_properties{count};
	instance.enumeratePhysicalDevices(&count, &device_properties[0]);

	if (device_properties.size() <= 0)
		throw std::runtime_error("No vulkan devices available!");

	// TODO: better device selection

	auto deviceIt = device_properties.begin();
	while (deviceIt != device_properties.end())
	{
		std::vector<vk::QueueFamilyProperties>  family_properties =
			device_properties[DEFAULT_DEVICE_INDEX].getQueueFamilyProperties();

		vk::PhysicalDevice device;
		int familyIndex = 0;
		auto family_it = family_properties.begin();
		while (family_it != family_properties.end())
		{
			if (glfwGetPhysicalDevicePresentationSupport(instance,
				device_properties[DEFAULT_DEVICE_INDEX], familyIndex) &&
				family_it->queueFlags & vk::QueueFlagBits::eGraphics)
			{
				break;
			}

			family_it++;
			familyIndex++;
		}
		if (family_it == family_properties.end())
			continue;

		return { device_properties[0], familyIndex };
	}
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

	constexpr const char* REQUIRED_EXTENSIONS[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

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


vk::SurfaceFormatKHR VKImpl::selectFormat(vk::PhysicalDevice& physDevice, vk::SurfaceKHR& surface)
{
	unsigned surfaceFormatCount;
	physDevice.getSurfaceFormatsKHR(surface, &surfaceFormatCount, nullptr);
	std::vector<vk::SurfaceFormatKHR> availiableFormats(surfaceFormatCount);
	physDevice.getSurfaceFormatsKHR(surface, &surfaceFormatCount, &availiableFormats[0]);

	constexpr vk::SurfaceFormatKHR PREFERRED_FORMAT_ORDER[] = {vk::SurfaceFormatKHR{vk::Format::eB8G8R8A8Srgb, vk::ColorSpaceKHR::eSrgbNonlinear} };
	for(auto& preferred  : PREFERRED_FORMAT_ORDER)
	{
		for(auto& availiable  : availiableFormats)
		{
			if(availiable == preferred)
			{
				return preferred;
			}
		}
	}

	return availiableFormats[0];
}

static vk::PresentModeKHR selectPresentMode(std::vector<vk::PresentModeKHR>& availialePresentModes)
{
	constexpr vk::PresentModeKHR PREFERRED_PRESENT_MODE_ORDER[] = { vk::PresentModeKHR::eMailbox, vk::PresentModeKHR::eFifo };
	for (auto& preferred : PREFERRED_PRESENT_MODE_ORDER)
	{
		for (auto& availiable : availialePresentModes)
		{
			if (availiable == preferred)
			{
				return preferred;
			}
		}
	}

	return availialePresentModes[0];
}

vk::UniqueSwapchainKHR VKImpl::createSwapchain(vk::Device& device, vk::PhysicalDevice& physDeivce, vk::SurfaceKHR& surface, GLFWwindow* window, vk::SurfaceFormatKHR
                                               surfaceFormat, vk::SwapchainKHR oldSwapchain)
{
	#define MIN_IMAGE_COUNT 1

	vk::SurfaceCapabilitiesKHR surfaceCaps;
	physDeivce.getSurfaceCapabilitiesKHR(surface, &surfaceCaps);

	unsigned presentModeCount;
	physDeivce.getSurfacePresentModesKHR(surface, &presentModeCount, nullptr);
	std::vector<vk::PresentModeKHR> availiablePresentModes(presentModeCount);
	physDeivce.getSurfacePresentModesKHR(surface, &presentModeCount, &availiablePresentModes[0]);

	vk::PresentModeKHR presentMode = selectPresentMode(availiablePresentModes);

	glm::ivec2 windowSize;
	glfwGetWindowSize(window, &windowSize.x, &windowSize.y);
	vk::Extent2D windowExtent{static_cast<unsigned>(windowSize.x), static_cast<unsigned>(windowSize.y)};

	vk::SwapchainCreateInfoKHR swapchain_info
	{
		{},
		surface,
		MIN_IMAGE_COUNT,
		surfaceFormat.format,
		surfaceFormat.colorSpace,
		windowExtent,
		1,
		vk::ImageUsageFlagBits::eColorAttachment,
		vk::SharingMode::eExclusive,
		0,
		nullptr,
		surfaceCaps.currentTransform,
		vk::CompositeAlphaFlagBitsKHR::eOpaque,
		presentMode,
		true,
		oldSwapchain,
		nullptr
	};

	return std::move(device.createSwapchainKHRUnique(swapchain_info));
}

std::vector<vk::UniqueImageView> VKImpl::defaultImageViews(vk::Device& device, vk::SwapchainKHR& swapchain, vk::Format format)
{
	std::vector<vk::UniqueImageView> views;

	vk::ImageViewCreateInfo imageviewInfo
	{
		{},
		{},
		vk::ImageViewType::e2D,
		format,
		vk::ComponentMapping {},
		vk::ImageSubresourceRange{
			vk::ImageAspectFlagBits::eColor,
			0,
			1,
			0,
			1
		}
	};

	std::vector<vk::Image> images = device.getSwapchainImagesKHR(swapchain);

	for(auto& image : images)
	{
		imageviewInfo.image = image;
		views.push_back(device.createImageViewUnique(imageviewInfo));
	}

	return views;
}
