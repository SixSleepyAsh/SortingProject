#include "DebugSystem.h"
#include "GraphicsSystem.h"


DebugSystem* DebugSystem::s_Instance = nullptr; 

void DebugSystem::OnInit()
{
    _window = GraphicsSystem::GetInstance()->getWindow();
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    ImFont* font = io->Fonts->AddFontDefault();
    if (font) {
        font->Scale = 1.3f;  // Increase the scale to make the font larger
    }
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui_ImplGlfw_InitForVulkan(_window, true);

    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = Graphics()->GetVulkanInstance();
    init_info.PhysicalDevice = Graphics()->GetPhysicalDevice();
    init_info.Device = Graphics()->GetLogicalDevice();
    init_info.QueueFamily = Graphics()->GetQueueFamilyIndex();
    init_info.Queue = Graphics()->GetQueue();
    init_info.PipelineCache = VK_NULL_HANDLE;
    init_info.DescriptorPool = Graphics()->GetDescriptorPool();
    init_info.Allocator = nullptr;
    init_info.MinImageCount = 2;
    init_info.ImageCount = Graphics()->GetImageCount();
    init_info.CheckVkResultFn = nullptr;  


    ImGui_ImplVulkan_Init(&init_info, GraphicsSystem::GetInstance()->GetRenderPass());
    ImGui_ImplVulkan_CreateFontsTexture(GraphicsSystem::GetInstance()->GetCommandBuffer());


    //ImGui::StyleColorsClassic();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // Stays at the Top
}

void DebugSystem::OnFixedUpdate()
{

}

void DebugSystem::OnUpdate(float dt)
{


    SelectionMenu();

    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();
    ImGui_ImplVulkan_RenderDrawData(draw_data, Graphics()->GetCommandBuffer());

    ImguiStartFrame();
}

void DebugSystem::OnExit()
{
    ImGui::Render();
    ImGui_ImplVulkan_Shutdown();
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

DebugSystem::DebugSystem() : System("Debug"), 
io(nullptr), _window(nullptr)
{
}
