#pragma once
#include "System.h"


///*****************************************************************/
/// Includes:
///*****************************************************************/
#include "basics.h"
#include "System.h"
#include <vector>
#include "imgui/imgui.h"
#include <imgui/imgui_impl_vulkan.h>
#include <imgui/imgui_impl_glfw.h>
#include <iostream>
#include <sstream>
#include <set>
///*****************************************************************/




class DebugSystem : public System
{
///---------------------------------------------------------------------
public: /// Virtual Methods
///---------------------------------------------------------------------

	virtual void OnInit() override;

	virtual void OnFixedUpdate() override;

	virtual void OnUpdate(float dt) override;

	virtual void OnExit() override;

///---------------------------------------------------------------------
public: /// Accessors
///---------------------------------------------------------------------

	static DebugSystem* GetInstance();


///---------------------------------------------------------------------
private: /// Members
///---------------------------------------------------------------------

	/// @brief Pointer to the ImGui Input/Output structure
	ImGuiIO* io;

	/// @brief The GLFW window handle
	GLFWwindow* _window;

	

///---------------------------------------------------------------------
private: /// Methods
///---------------------------------------------------------------------

	void ImguiStartFrame();


	void SelectionMenu();

///---------------------------------------------------------------------
private: /// Singleton Stuff
///---------------------------------------------------------------------
 	static DebugSystem* s_Instance;

	DebugSystem() : System("Debug") {}
};

/// @brief shorthand for getting the DebugSystem
/// @return instance of the DebugSyste
__inline DebugSystem& Debug() { return *DebugSystem::GetInstance(); }


