#pragma once 
#include "nlohmann/json.hpp"
#include "Array.hpp"
#include "String.hpp"
#include <cstdint>

namespace Sol {
namespace glTF {

using Json = nlohmann::json;

Json read_json(const char* file);

// Asset
struct Asset {
  // TODO:: Add minVerison support
  StringBuffer version;  
  StringBuffer copyright;

  void fill(Json json);
};

// Scenes
struct Scene {
  Array<uint32_t> nodes;
  StringBuffer name;

  void fill(Json json);
};
struct Scenes {
  Array<Scene> scenes;
  uint32_t scene = UINT32_MAX;
  void fill(Json json);
};

// Nodes
struct Node {
  Array<float> rotation;
  Array<float> scale;
  Array<float> translation;
  Array<float> matrix;

  Array<uint32_t> children;
  StringBuffer name;
  uint32_t mesh = UINT32_MAX;
  uint32_t camera = UINT32_MAX;

  void fill(Json json);
};
struct Nodes {
  Array<Node> nodes;
  void fill(Json json);
};

// Buffers & BufferViews
struct Buffer {
  size_t byte_length;
  StringBuffer uri;
  void fill(Json json);
};
struct Buffers {
  Array<Buffer> buffers;
  void fill(Json json);
};
struct BufferView {
  enum Target {
    NONE = 0,
    ARRAY_BUFFER = 34962,
    ELEMENT_ARRAY_BUFFER = 34963,
  };
  size_t byte_length = UINT64_MAX;
  size_t byte_offset = UINT64_MAX;
  size_t byte_stride = UINT64_MAX;
  uint32_t buffer = UINT32_MAX;
  Target target = NONE;

  void fill(Json json);
};
struct BufferViews {
  Array<BufferView> views;
  void fill(Json json);
};

// Accessors
struct Accessor {
  enum ComponentType {
    NONE = 0,
    INT8 = 5120,
    UINT8 = 5121,
    INT16 = 5122,
    UINT16 = 5123,
    UINT32 = 5125,
    FLOAT = 5126,
  };
  struct Sparse {
    struct Indices {
      size_t byte_offset = UINT64_MAX;
      uint32_t buffer_view = UINT32_MAX;
      ComponentType component_type = NONE;
      void fill(Json json);
    };
    struct Values {
      size_t byte_offset = UINT64_MAX;
      uint32_t buffer_view = UINT32_MAX;
      void fill(Json json);
    };
    Indices indices;
    Values values;
    size_t count = UINT64_MAX;
    void fill(Json json);
  };

  Sparse sparse;
  Array<size_t> max;
  Array<size_t> min;
  StringBuffer type;
  ComponentType component_type = NONE;

  size_t byte_offset = UINT64_MAX;
  size_t count = UINT64_MAX;
  uint32_t buffer_view = UINT32_MAX;

  void fill(Json json);
};
struct Accessors {
  Array<Accessor> accessors;
  void fill(Json json);
};

struct glTF {
  Asset asset;
  Scenes scenes;
  Nodes nodes;
  Buffers buffers;
  BufferViews buffer_views;
  Accessors accessors;

  void fill(Json json);
};

} // namespace glTF
} // namespace Sol
