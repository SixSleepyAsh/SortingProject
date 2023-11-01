#include "DebugSystem.h"

#include "GraphicsSystem.h"

static void SetupVulkanWindow(ImGui_ImplVulkanH_Window* window, vk::SurfaceKHR surface, int width, int height, VkPhysicalDevice g_PhysicalDevice, uint32_t g_QueueFamily, VkInstance g_Instance, VkDevice g_Device, uint32_t g_MinImageCount)
{
    window->Surface = surface;

    VkBool32 res;
    vkGetPhysicalDeviceSurfaceSupportKHR(g_PhysicalDevice, g_QueueFamily, window->Surface, &res);
    if (res != VK_TRUE)
    {
        throw std::runtime_error("Failed to setup WSI suppport?");
    }

    const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
    const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    window->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(g_PhysicalDevice, window->Surface, requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

    // Select Present Mode
#ifdef IMGUI_UNLIMITED_FRAME_RATE
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR };
#else
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_FIFO_KHR };
#endif
    window->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(g_PhysicalDevice, window->Surface, &present_modes[0], IM_ARRAYSIZE(present_modes));
    //printf("[vulkan] Selected PresentMode = %d\n", wd->PresentMode);

    // Create SwapChain, RenderPass, Framebuffer, etc.
    IM_ASSERT(g_MinImageCount >= 2);
    ImGui_ImplVulkanH_CreateOrResizeWindow(g_Instance, g_PhysicalDevice, g_Device, window, g_QueueFamily, nullptr, width, height, g_MinImageCount);
}

void DebugSystem::OnInit()
{
    _window /*Get Window Handle*/;
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    ImFont* font = io->Fonts->AddFontDefault();
    if (font) 
    {
        font->Scale = 1.3f;  // Increase the scale to make the font larger
    }

    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui_ImplGlfw_InitForOpenGL(_window, true);

    ImGui_ImplVulkanH_Window* mainWindow;

    ImGui::StyleColorsClassic(); /// | ImGui::StyleColorsDark();  | /// ImGui::StyleColorsLight();

    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui_ImplGlfw_InitForVulkan(GraphicsSystem::GetInstance()->getWindow(), true);
    /*ImGui_ImplVulkan_InitInfo init_info = {
        GraphicsSystem::GetInstance()->getVkInstance(),
        GraphicsSystem::GetInstance()->getVkPhysicalDevice(),
        GraphicsSystem::GetInstance()->getLogicalDevice(),
        GraphicsSystem::GetInstance()->getQueueFamily(),
        GraphicsSystem::GetInstance()->getQueue(),
        GraphicsSystem::GetInstance()->getPipelineCache(),
        GraphicsSystem::GetInstance()->getDescriptorPool(),
        0,
        GraphicsSystem::GetInstance()->getMinImageCount(),
        GraphicsSystem::GetInstance()->getImageCount(),
        VK_SAMPLE_COUNT_1_BIT,
        false,
        GraphicsSystem::GetInstance()->getFormat(),
        nullptr,
        nullptr
    };
    ImGui_ImplVulkan_Init(&init_inifo, )*/

    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void DebugSystem::OnFixedUpdate()
{

}

void DebugSystem::OnUpdate(float dt)
{


    SelectionMenu();

    ImGui::Render();
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImguiStartFrame();
}

void DebugSystem::OnExit()
{
    ImGui::Render();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

DebugSystem* DebugSystem::GetInstance()
{
	if (s_Instance == nullptr)
	{
		s_Instance = new DebugSystem();
	}

	return s_Instance;
}

void DebugSystem::ImguiStartFrame()
{
    auto& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    //ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void DebugSystem::SelectionMenu()
{
    static bool selection_window = true;
    ImGui::Begin("Editor Window", &selection_window, ImGuiWindowFlags_MenuBar);
    ImGui::SetWindowSize(ImVec2(700, 700), ImGuiCond_FirstUseEver);
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);


    ImGui::End();
}
