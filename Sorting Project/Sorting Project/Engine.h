

#pragma once
#include "System.h"
#include <vector>
#include <string>
#include <map>

class Engine{

//-----------------------------------------------------------------------------
public: // methods
//-----------------------------------------------------------------------------

	/// @brief  Starts running the engine. Code will not advance past this point until the engine stops running.
	void Run();

	/// @brief  Flags the engine to close once it finishes this loop
	void Close();

    /// @brief Adds a system to the engine
    /// @param system - the system to add
    void AddSystem( System * system );

//-----------------------------------------------------------------------------
public: // accessors
//-----------------------------------------------------------------------------

    /// @brief  gets the duration of each fixed frame
    /// @return the amount of time in seconds that each fixed frame lasts
    float GetFixedFrameDuration() const;

    /// @brief  sets the duration of each fixed frame
    /// @param  fixedFrameDuration  the amount of time in seconds that each fixed frame lasts
    void SetFixedFrameDuration( float fixedFrameDuration );

    /// @brief  gets the array of all Systems in the engine.
    /// @return the array of all Systems in the engine
    std::vector< System * > const& GetSystems() const;

private: // methods


//-----------------------------------------------------------------------------
private: // member variables
//-----------------------------------------------------------------------------

    /// @brief  Container of all the Systems in the engine
    std::vector< System * > m_Systems;

    /// @brief  flag set to true when the engine needs to exit
    bool m_ShouldExit;

    /// @brief  The timestamp of the previous frame
    double m_PreviousTime;

    /// @brief  The timestamp of the previous fixed frame
    double m_PreviousFixedTime;

    /// @brief  The duration of each fixed frame
    float m_FixedFrameDuration;


//-----------------------------------------------------------------------------
private: // methods
//-----------------------------------------------------------------------------

    /// @brief  Loads the engine config from "Data/EngineConfig.json"
    void load();

    /// @brief  Initializes the engine and all Systems in the Engine.
    void init();

    /// @brief  Updates the engine each frame
    void update();

    /// @brief  Calls all Systems in the Engine's Update function
    void updateSystems( float dt );

    /// @brief  Calls all Systems in the Engine's FixedUpdate function
    void fixedUpdateSystems();

    /// @brief  exits and closes the Engine
    void exit();


//-----------------------------------------------------------------------------
private: // singleton stuff
//-----------------------------------------------------------------------------

    /// @brief  The singleton instance of the Engine
    static Engine * s_Instance;

    /// @brief  Constructs a new Engine
    Engine();


//-----------------------------------------------------------------------------
public: // singleton stuff
//-----------------------------------------------------------------------------

    /// @brief  gets the singleton instance of the Engine
    /// @return the singleton instance of the Engine
    static Engine * GetInstance();

    // Prevent Engine from being copied
    Engine( Engine& other ) = delete;
    void operator=( const Engine& ) = delete;

};


__inline Engine* GameEngine()
{
    return Engine::GetInstance();
}