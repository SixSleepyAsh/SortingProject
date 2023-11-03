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

public:
	GraphicsSystem() : System("Graphics System") {}

	static GraphicsSystem* GetInstance();

	GLFWwindow* getWindow();;

	void OnInit() override;
	void OnFixedUpdate() override;
	void OnUpdate(float dt) override;
	void OnExit() override;;
};