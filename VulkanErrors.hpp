#pragma once
//#include <vulkan/vulkan.hpp>
#include <iostream>

namespace Sol {

struct VulkanError {
  //static const char* match_error(VkResult error);
};

#define ABORT(test, msg) \
  if(!(test)) { \
    std::cerr << "ABORT in " << __FILE__ << ", line " << __LINE__ << ": " << msg << '\n'; \
    abort(); \
  }

#if V_LAYERS

#if 0
#define DEBUG_OBJ_CREATION(creation_func, err_code)  \
  if (err_code != VK_SUCCESS) { \
    const char* err_msg = (VulkanError::match_error(err_code)); \
    std::cerr << "OBJ CREATION ERROR: " << #creation_func << \
    " returned " << err_msg << ", (" << __FILE__ << ", " << __LINE__ << ")\n";  \
    abort(); \
  } 
#endif

#define DEBUG_ABORT(test, msg) \
  if (!(test)) { \
    std::cerr << "DEBUG_ABORT in " << __FILE__ << ", line " << __LINE__ << ": " << msg << '\n'; \
    abort(); \
  }

#else 

#define DEBUG_ABORT(test, msg) {}

#define DEBUG_OBJ_CREATION(creation_func, err_code)  {}

#endif



} // Sol
