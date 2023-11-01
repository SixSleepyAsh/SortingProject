#include "Engine.h"

#include "GraphicsSystem.h"
#include "InputSystem.h"
#include "basics.h"

void Engine::Run()
{
    init();

    while (
        m_ShouldExit == false &&
        Input()->GetKeyTriggered(GLFW_KEY_ESCAPE) == false
        )
    {
        update();
    }

    exit();
}

void Engine::Close()
{
   m_ShouldExit = true;
}

void Engine::AddSystem(System* system)
{
    m_Systems.emplace_back(system);
}

float Engine::GetFixedFrameDuration() const
{
	return m_FixedFrameDuration;
}

void Engine::SetFixedFrameDuration(float fixedFrameDuration)
{
	m_FixedFrameDuration = fixedFrameDuration;
}

std::vector<System*> const& Engine::GetSystems() const
{
	return m_Systems;
}

void Engine::load()
{
}

void Engine::init()
{

   // Debug() << "Starting up..." << std::endl;

    // initialize the time values
    m_PreviousTime = glfwGetTime();
    m_PreviousFixedTime = m_PreviousTime;

    // initialize all the systems
    for (System* system : m_Systems)
    {
        system->OnInit();
      //  Debug() << "Starting " << system->GetName() << std::endl << std::endl;
    }

    // Set the clear color (background color)
    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Engine::update()
{
    double currentTime = glfwGetTime();

    updateSystems(static_cast<float>(currentTime - m_PreviousTime));

    if (currentTime - m_PreviousFixedTime > m_FixedFrameDuration)
    {
        fixedUpdateSystems();

        if (currentTime - m_PreviousFixedTime <= -m_FixedFrameDuration)
        {
            m_PreviousFixedTime = currentTime;
        }
        else
        {
            m_PreviousFixedTime += m_FixedFrameDuration;
        }
    }

    m_PreviousTime = currentTime;

    /*GLFWwindow* window /*Get WindowHandle#1#;

    // ensure viewport size matches window size
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    // Swap front and back buffers
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT);


    glfwPollEvents();*/

}

void Engine::updateSystems(float dt)
{
    for (System* system : m_Systems)
    {
        system->OnUpdate(dt);
    }
}

void Engine::fixedUpdateSystems()
{
    for (System* system : m_Systems)
    {
	    system->OnFixedUpdate();
	}
}

void Engine::exit()
{
   /// Debug() << std::endl << std::endl << "Exiting..."
    ///    << std::endl << std::endl;
    for (System* system : m_Systems)
    {
        system->OnExit();

      ///  Debug() << "Exiting " << system->GetName()
      ///      << std::endl << std::endl;
    }

  ///  Debug() << "\nShutdown complete." << std::endl;

}


/// @brief  Constructs a new Engine
Engine::Engine() :
    m_ShouldExit(false),
    m_FixedFrameDuration(1.0f / 60.0f),
    m_PreviousFixedTime(0.0),
    m_PreviousTime(0.0)
{}

Engine* ENGINE = {};

/// @brief  gets the singleton instance of the Engine
/// @return the singleton instance of the Engine
Engine* Engine::GetInstance()
{
    if (ENGINE == nullptr)
    {
		ENGINE = new Engine();
	}

	return ENGINE;
}
