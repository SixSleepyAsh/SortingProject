#pragma once

#include <map>
#include "System.h"
#include "glm/glm.hpp"


using namespace std;

class InputSystem : public System
{
    //-----------------------------------------------------------------------------
private: // virtual override methods
    //-----------------------------------------------------------------------------

        /// @brief fixed update for input, must be called for input to function
    virtual void OnFixedUpdate() override;

    //-----------------------------------------------------------------------------

         /// @brief Constructs the InputSystem
    InputSystem();


    /// @brief The singleton instance of InputSystem
    static InputSystem* instance;
protected:

    map<int, bool[3]> m_KeyStates;
    map<int, bool[3]> m_MouseStates;

public:

    /// @brief gets the instance of InputSystem
    /// @return the instance of the InputSystem
    static InputSystem* GetInstance();

    /// @brief checks if a given key is down
    /// @param glfw key to check
    /// @return returns if key is down
    bool GetKeyDown(int glfw_key);

    /// @brief checks if a given key is up
    /// @param glfw key to check
    /// @return returns if key is up
    bool GetKeyUp(int glfw_key);

    /// @brief checks if a given key is triggered
    /// @param glfw key to check
    /// @return returns if key is triggered
    bool GetKeyTriggered(int glfw_key);

    /// @brief checks if a given key is released
    /// @param glfw key to check
    /// @return returns if key is released
    bool GetKeyReleased(int glfw_key);

    /// @brief checks if a given mouse button is down
    /// @param glfw mouse button to check
    /// @return returns if mouse button is down
    bool GetMouseDown(int glfw_mouse_button);

    /// @brief checks if a given mouse button is up
    /// @param glfw mouse button to check
    /// @return returns if mouse button is up
    bool GetMouseUp(int glfw_mouse_button);

    /// @brief checks if a given mouse button is triggered
    /// @param glfw mouse button to check
    /// @return returns if mouse button is triggered
    bool GetMouseTriggered(int glfw_mouse_button);

    /// @brief checks if a given mouse button is released
    /// @param glfw mouse button to check
    /// @return returns if mouse button is released
    bool GetMouseReleased(int glfw_mouse_button);

    // Prevent copying
    InputSystem(InputSystem& other) = delete;
    void operator=(const InputSystem&) = delete;

	void OnInit() override;
    void OnUpdate(float dt) override;
    void OnExit() override;
};

/// @brief shortens input get instance to simply input
/// @return returns the input system instance
__inline InputSystem* Input() { return InputSystem::GetInstance(); }