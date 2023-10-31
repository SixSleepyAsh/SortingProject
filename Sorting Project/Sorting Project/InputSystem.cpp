
#include "InputSystem.h"
#include <map>
#include "glfw3.h"

/// @brief fixed update for input, must be called
void InputSystem::OnFixedUpdate()
{
    for (auto& key : m_KeyStates)
    {
        bool old = key.second[0];
        key.second[0] = glfwGetKey(/*Get WindowHandle*/,
            key.first);

        if (key.second[0] == true && old == false)
        {
            key.second[1] = true;
        }
        else
        {
            key.second[1] = false;
        }
        if (key.second[0] == false && old == true)
        {
            key.second[2] = true;
        }
        else
        {
            key.second[2] = false;
        }
    }

    for (auto& key : m_MouseStates)
    {
        bool old = key.second[0];
        key.second[0] = glfwGetMouseButton(/*Get WindowHandle*/,
            key.first);

        if (key.second[0] == true && old == false)
        {
            key.second[1] = true;
        }
        else
        {
            key.second[1] = false;
        }
        if (key.second[0] == false && old == true)
        {
            key.second[2] = true;
        }
        else
        {
            key.second[2] = false;
        }
    }
}

/// @brief checks if a given key is down
/// @param glfw key to check
/// @return returns if key is down
bool InputSystem::GetKeyDown(int glfw_key)
{
    return m_KeyStates[glfw_key][0];
}

/// @brief checks if a given key is up
/// @param glfw key to check
/// @return returns if key is up
bool InputSystem::GetKeyUp(int glfw_key)
{
    return !GetKeyDown(glfw_key);
}

/// @brief checks if a given key is triggered
/// @param glfw key to check
/// @return returns if key is triggered
bool InputSystem::GetKeyTriggered(int glfw_key)
{
    return m_KeyStates[glfw_key][1];
}

/// @brief checks if a given key is released
/// @param glfw key to check
/// @return returns if key is released
bool InputSystem::GetKeyReleased(int glfw_key)
{
    return m_KeyStates[glfw_key][2];
}


/// @brief checks if a given mouse button is down
/// @param glfw mouse button to check
/// @return returns if mouse button is down
bool InputSystem::GetMouseDown(int glfw_mouse_button)
{
    return m_MouseStates[glfw_mouse_button][0];
}

/// @brief checks if a given mouse button is up
/// @param glfw mouse button to check
/// @return returns if mouse button is up
bool InputSystem::GetMouseUp(int glfw_mouse_button)
{
    return !GetMouseDown(glfw_mouse_button);
}

/// @brief checks if a given mouse button is triggered
/// @param glfw mouse button to check
/// @return returns if mouse button is triggered
bool InputSystem::GetMouseTriggered(int glfw_mouse_button)
{
    return m_MouseStates[glfw_mouse_button][1];
}

/// @brief checks if a given mouse button is released
/// @param glfw mouse button to check
/// @return returns if mouse button is released
bool InputSystem::GetMouseReleased(int glfw_mouse_button)
{
    return m_MouseStates[glfw_mouse_button][2];
}

//-----------------------------------------------------------------------------
// singleton stuff
//-----------------------------------------------------------------------------

    /// @brief Constructs the InputSystem
InputSystem::InputSystem() :
    System("InputSystem")
{}

/// @brief The singleton instance of InputSystem
InputSystem* InputSystem::instance = nullptr;

/// @brief gets the instance of InputSystem
/// @return the instance of the InputSystem
InputSystem* InputSystem::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new InputSystem();
    }
    return instance;
}

//-----------------------------------------------------------------------------
