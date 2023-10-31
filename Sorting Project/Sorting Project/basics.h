#pragma once

#include <glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <atomic>
#include <typeindex>


/// @brief  gets a unique ID value every time this function is called
/// @return the unique ID
__inline unsigned GetUniqueId()
{
    static std::atomic< unsigned > id{ 0 };
    return ++id;
}