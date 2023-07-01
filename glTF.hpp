#pragma once 
#include "nlohmann/json.hpp"
#define V_LAYERS true
#include "Array.hpp"
#include "String.hpp"

#include <cstdint>
#include <limits>

namespace Sol {
namespace glTF {

using Json = nlohmann::json;

Json read_json(const char* file);

extern const int32_t INVALID_INDEX;
extern const uint32_t INVALID_COUNT;
extern const float INVALID_FLOAT;
extern const uint8_t PNG_BYTE_PATTERN[8];
extern const uint8_t JPG_BYTE_PATTERN[3];
extern const int32_t NEAREST_FALLBACK;
extern const int32_t LINEAR_FALLBACK;

// Asset
struct Asset {
  // TODO:: Add minVerison support
  StringBuffer version;  
  StringBuffer copyright;

  void fill(Json json);
};

// Scenes
struct Scene {
  Array<int32_t> nodes;
  StringBuffer name;

  void fill(Json json);
};
struct Scenes {
  Array<Scene> scenes;
  int32_t scene = INVALID_INDEX;
  void fill(Json json);
};

// Nodes
struct Node {
  Array<float> rotation;
  Array<float> scale;
  Array<float> translation;
  Array<float> matrix;
  Array<float> weights;

  Array<int32_t> children;
  StringBuffer name;
  int32_t mesh = INVALID_INDEX;
  int32_t skin = INVALID_INDEX;
  int32_t camera = INVALID_INDEX;

  void fill(Json json);
};
struct Nodes {
  Array<Node> nodes;
  void fill(Json json);
};

// Buffers & BufferViews
struct Buffer {
  uint32_t byte_length;
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
  uint32_t byte_length = INVALID_COUNT;
  uint32_t byte_offset = INVALID_COUNT;
  uint32_t byte_stride = INVALID_COUNT;
  int32_t buffer = INVALID_INDEX;
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
  enum Type {
    SCALAR,
    VEC2,
    VEC3,
    VEC4,
    MAT2,
    MAT3,
    MAT4,
  };
  struct Sparse {
    struct Indices {
      uint32_t byte_offset = INVALID_COUNT;
      int32_t buffer_view = INVALID_INDEX;
      ComponentType component_type = NONE;
      void fill(Json json);
    };
    struct Values {
      uint32_t byte_offset = INVALID_COUNT;
      int32_t buffer_view = INVALID_INDEX;
      void fill(Json json);
    };
    Indices indices;
    Values values;
    uint32_t count = INVALID_COUNT;
    void fill(Json json);
  };

  Sparse sparse;
  Array<float> max;
  Array<float> min;
  Type type;
  ComponentType component_type = NONE;

  uint32_t byte_offset = INVALID_COUNT;
  uint32_t count = INVALID_COUNT;
  int32_t buffer_view = INVALID_INDEX;

  void fill(Json json);
};
struct Accessors {
  Array<Accessor> accessors;
  void fill(Json json);
};

// Meshes
struct Mesh {
  struct Primitive {
    struct Attribute {
      StringBuffer key;
      int32_t accessor = INVALID_INDEX;
    };
    struct Target {
      Array<Attribute> attributes;
      void fill(Json json);
    };

    Array<Attribute> attributes;
    Array<Target> targets;
    int32_t indices = INVALID_INDEX;
    int32_t material = INVALID_INDEX;
    int32_t mode = INVALID_INDEX;

    static void fill_attrib_array(Json json, Array<Attribute> *attributes);
    void fill(Json json);
  };
  struct Extras {
    Array<StringBuffer> target_names;
    void fill(Json json);
  };

  Array<Primitive> primitives;
  Array<float> weights;
  Extras extras;

  void fill(Json json);
};
struct Meshes {
  Array<Mesh> meshes;
  void fill(Json json);
};

// Skins
struct Skin {
  Array<int32_t> joints;
  int32_t i_bind_matrices = INVALID_INDEX;
  int32_t skeleton = INVALID_INDEX;
  void fill(Json json);
};
struct Skins {
  Array<Skin> skins;
  void fill(Json json);
};

// Textures
struct Texture {
  int32_t sampler = INVALID_INDEX;
  int32_t source = INVALID_INDEX;
  void fill(Json json);
};
struct Textures {
  Array<Texture> textures;
  void fill(Json json);
};

// Images
struct Image {
  StringBuffer uri;
  StringBuffer mime_type;
  int32_t buffer_view = INVALID_INDEX;

  void fill(Json json);
};
struct Images {
  Array<Image> images;
  void fill(Json json);
};

// Samplers
struct Sampler {
  enum class Filter {
    NONE = 0,
    NEAREST = 9728,
    LINEAR = 9729,
    NEAREST_MIPMAP_NEAREST = 9984,
    LINEAR_MIPMAP_NEAREST = 9985,
    NEAREST_MIPMAP_LINEAR = 9986,
    LINEAR_MIPMAP_LINEAR = 9987,
  };
  enum class Wrap {
    NONE = 0,
    CLAMP_TO_EDGE = 33071,
    MIRRORED_REPEAT = 33648,
    REPEAT = 10497,
  };
  Filter mag_filter = Filter::NONE;
  Filter min_filter = Filter::NONE;
  Wrap wrap_s = Wrap::NONE;
  Wrap wrap_t = Wrap::NONE;

  void fill(Json json);
};
struct Samplers {
  Array<Sampler> samplers;
  void fill(Json json);
};

// Materials
struct Material {
  struct Texture {
    float scale = INVALID_FLOAT;
    int32_t index = INVALID_INDEX;
    int32_t tex_coord = INVALID_INDEX;

    void fill_tex(Json json, const char* key);
  };
  struct PbrMetallicRoughness {
    Array<float> base_color_factor;
    Texture base_color_texture;
    Texture metallic_roughness_texture;
    float metallic_factor = INVALID_FLOAT;
    float roughness_factor = INVALID_FLOAT;

    void fill(Json json);
  };
  enum AlphaMode {
    OPAQUE,
    MASK,
    BLEND,
  };

  PbrMetallicRoughness pbr_metallic_roughness;
  Array<float> emissive_factor;
  StringBuffer name;
  Texture normal_texture;
  Texture occlusion_texture;
  Texture emissive_texture;
  AlphaMode alpha_mode = OPAQUE;
  float alpha_cutoff = INVALID_FLOAT;
  bool double_sided = false;

  void fill(Json json);
};
struct Materials {
  Array<Material> materials;
  void fill(Json json);
};

// Cameras 
struct Camera {
  enum Type {
    UNKNOWN,
    ORTHO,
    PERSPECTIVE,
  };
  StringBuffer name;
  Type type = UNKNOWN;
  float aspect_ratio = INVALID_FLOAT;
  float yfov = INVALID_FLOAT;
  float xmag = INVALID_FLOAT;
  float ymag = INVALID_FLOAT;
  float zfar = INVALID_FLOAT;
  float znear = INVALID_FLOAT;

  void fill(Json json);
};
struct Cameras {
  Array<Camera> cameras;
  void fill(Json json);
};

// glTF 
struct glTF {
  Asset asset;
  Scenes scenes;
  Nodes nodes;
  Buffers buffers;
  BufferViews buffer_views;
  Accessors accessors;
  Meshes meshes;
  Skins skins;
  Textures textures;
  Images images;
  Samplers samplers;
  Materials materials;
  Cameras cameras;

  void fill(Json json);
};

} // namespace glTF
} // namespace Sol
