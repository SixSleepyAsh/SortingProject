#pragma once
#include "basics.h"

class System
{

    //-----------------------------------------------------------------------------
public:
    virtual ~System() = default;
    // virtual methods
//-----------------------------------------------------------------------------

    /// @brief  Gets called once when this System is added to the Engine
    virtual void OnInit() = 0;

    /// @brief  Gets called once every simulation frame. Use this function for anything that affects the simulation.
    virtual void OnFixedUpdate() = 0 ;

    /// @brief  Gets called once every graphics frame. Do not use this function for anything that affects the simulation.
    /// @param  dt  the elapsed time in seconds since the previous frame
    virtual void OnUpdate(float dt) = 0;

    /// @brief  Gets called once before the Engine closes
    virtual void OnExit() = 0;

//-----------------------------------------------------------------------------
public: // accessors
//-----------------------------------------------------------------------------
	/// @brief  gets this System's ID
    /// @return this System's ID
    unsigned GetId() const { return m_Id; }


//-----------------------------------------------------------------------------
protected: // constructor
//-----------------------------------------------------------------------------
    
    /// @brief  Constructs a System
    System( std::string const& name ) :
        m_Name( name )
    {
        m_Id = GetUniqueId();
    }

//-----------------------------------------------------------------------------
public: // singleton stuff
//-----------------------------------------------------------------------------
    
    // Prevent Systems from being copied
    System( System& other ) = delete;
    void operator=( const System& ) = delete;

//-----------------------------------------------------------------------------
private: // member variables
//-----------------------------------------------------------------------------

    /// @brief The Unique Name of this System to be used for Debug Window
    std::string m_Name = "";

    /// @brief  the Id of this System
    unsigned m_Id = 0;

    /// @brief  whether this System will update
    bool m_Enabled = true;

    bool m_ShowDebugWindow = false;


};

