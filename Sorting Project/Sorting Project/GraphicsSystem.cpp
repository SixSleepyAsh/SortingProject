#include "GraphicsSystem.h"

#include "VulkanImpl.h"

GraphicsSystem* GRAPHICS_SYSTEM = {};

GraphicsSystem* GraphicsSystem::GetInstance()
{
	if (GRAPHICS_SYSTEM == nullptr)
		GRAPHICS_SYSTEM = new GraphicsSystem();
	return GRAPHICS_SYSTEM;
}

GLFWwindow* GraphicsSystem::getWindow()
{
	return m_window;
}

void GraphicsSystem::OnInit()
{
	if(!glfwInit())
	{
		throw std::runtime_error("GLFW failed to initialize");
	}

	if (!glfwVulkanSupported())
	{
		throw std::runtime_error("Vulkan is not supported");
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_window = glfwCreateWindow(640, 480, "Window Title", NULL, NULL);

	uint32_t extension_count;
	const char** required_extensions = glfwGetRequiredInstanceExtensions(&extension_count);

	m_instance = VKImpl::createVulkanInstance(required_extensions, extension_count);
	
	auto physDevicePair = VKImpl::SelectVulkanDevice(*m_instance);
	m_physDevice = physDevicePair.first;
	m_selectedQueue = physDevicePair.second;
	
	m_logicalDevice = VKImpl::createLogicalDevice(m_instance, m_physDevice, m_selectedQueue);
}

void GraphicsSystem::OnFixedUpdate()
{
}

void GraphicsSystem::OnUpdate(float dt)
{
}

void GraphicsSystem::OnExit()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

