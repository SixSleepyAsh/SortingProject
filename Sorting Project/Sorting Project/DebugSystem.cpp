#include "DebugSystem.h"

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
    ImGui_ImplOpenGL3_Init("#version 430");

    ImGui::StyleColorsClassic(); /// | ImGui::StyleColorsDark();  | /// ImGui::StyleColorsLight();

    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplOpenGL3_NewFrame();
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
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

    ImGui_ImplOpenGL3_NewFrame();
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
