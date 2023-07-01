#define V_LAYERS true

#include "VulkanErrors.hpp"
#include "Allocator.hpp"
#include "Vec.hpp"
#include "Array.hpp"
#include "String.hpp"
#include "glTF.hpp"

#include <iostream>
#include <cstdint>
#include <string>

using namespace Sol;
using Alloc = LinearAllocator;

struct Thing {
  const char* str;
  uint32_t num;
};

using Json = nlohmann::json;
int main() {
  MemoryConfig mem_config;
  MemoryService::instance()->init(&mem_config);
  MemoryService::instance()->scratch_allocator.init(1024 * 1024);
  
  Json json;
  bool ok = glTF::read_json("test_1.json", &json);

  if (!ok) 
    ABORT(false, "File does not exist");

  glTF::glTF gltf;
  gltf.fill(json);

  MemoryService::instance()->shutdown();
  return 0;
}
