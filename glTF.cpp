#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include "glTF.hpp"
#include "nlohmann/json.hpp"
#include "VulkanErrors.hpp"

namespace Sol {
namespace glTF {

Json read_json(const char* file) {
  std::ifstream f(file);

  ABORT(f.is_open(), file);

  Json data = Json::parse(f);
  f.close();
  return data;
}

void glTF::fill(Json json) {
  asset.fill(json);
  scenes.fill(json); 
  nodes.fill(json);
  buffers.fill(json);
  buffer_views.fill(json);
  accessors.fill(json);
}

namespace { 
  template<typename T>
  static bool try_load_T(Json json, const char* key, T *obj) {
    auto tmp = json.find(key);
    if (tmp == json.end())
      return false;

    *obj = tmp.value();
    return true;
  }
  static bool try_load_string(Json json, const char* key, StringBuffer *str) {
    auto obj = json.find(key);
    if (obj == json.end())
      return false;

    std::string tmp = json.value(key, "");
    str->copy_here(tmp, tmp.length());
    return true;
  }
  template<typename T>
  static bool try_load_array(Json json, const char* key, Array<T> *array) {
    auto obj = json.find(key);
    if (obj == json.end())
      return false;

    size_t size = obj.value().size();
    array->init(size, 8);
    return true;
  }
}

// Asset /////////////////////////
void Asset::fill(Json json) {
  auto asset = json.find("asset");
  ABORT(asset != json.end(), "glTF has no 'asset' obj");

  try_load_string(asset.value(), "version", &version);
  ABORT(version.str, "glTF asset has no 'version' field");

  try_load_string(asset.value(), "copyright", &copyright);
}

// Scenes ///////////////////////
void Scenes::fill(Json json) {
  try_load_array(json, "scenes", &scenes);
  try_load_T(json, "scene", &scene);
  for(auto i : json["scenes"]) {
    Scene scene;
    scene.fill(i);
    scenes.push(scene);
  }
}
void Scene::fill(Json json) {
  try_load_string(json, "name", &name);
  try_load_array(json, "nodes", &nodes);
  for(auto i : json["nodes"]) 
    nodes.push(i);
}

// Nodes ////////////////////////
void Nodes::fill(Json json) {
  try_load_array(json, "nodes", &nodes);
  for(auto i : json["nodes"]) {
    Node node;
    node.fill(i);
    nodes.push(node);
  }
}
void Node::fill(Json json) {
  try_load_string(json, "name", &name);
  try_load_T(json, "mesh", &mesh);
  try_load_T(json, "camera", &camera);

  try_load_array(json, "rotation", &rotation);
  for(auto i : json["rotation"])
    rotation.push(i);
  try_load_array(json, "scale", &scale);
  for(auto i : json["scale"])
    scale.push(i);
  try_load_array(json, "translation", &translation);
  for(auto i : json["translation"])
    translation.push(i);

  try_load_array(json, "matrix", &matrix);
  for(auto i : json["matrix"])
    matrix.push(i);

  try_load_array(json, "children", &children);
  for(auto i : json["children"])
    children.push(i);
}

// Buffers & BufferViews //////////////////////
void Buffers::fill(Json json) {
  try_load_array(json, "buffers", &buffers);
  for(auto i : json["buffers"]) {
    Buffer buf;
    buf.fill(i);
    buffers.push(buf);
  }
}
void Buffer::fill(Json json) {
  try_load_T(json, "byteLength", &byte_length);
  try_load_string(json, "uri", &uri);
}

void BufferViews::fill(Json json) {
  try_load_array(json, "bufferViews", &views);
  for(auto i : json["bufferViews"]) {
    BufferView view;
    view.fill(i);
    views.push(view);
  }
}
void BufferView::fill(Json json) {
  try_load_T(json, "buffer", &buffer);
  try_load_T(json, "byteLength", &byte_length);
  try_load_T(json, "byteOffset", &byte_offset);
  try_load_T(json, "byteStride", &byte_stride);
  try_load_T(json, "target", &target);
}

// Accessors ///////////////////////
void Accessors::fill(Json json) {
  try_load_array(json, "accessors", &accessors);
  for(auto i : json["accessors"]) {
    Accessor accessor;
    accessor.fill(i);
    accessors.push(accessor);
  }
}
void Accessor::fill(Json json) {
  try_load_array(json, "max", &max);
  try_load_array(json, "min", &min);
  try_load_string(json, "type", &type);
  try_load_T(json, "componentType", &component_type);
  try_load_T(json, "byteOffset", &byte_offset);
  try_load_T(json, "count", &count);
  try_load_T(json, "bufferView", &buffer_view);

  Json json_sparse;
  if (try_load_T(json, "sparse", &json_sparse)) {
    sparse.fill(json_sparse);
  }
}
void Accessor::Sparse::fill(Json json) {
  try_load_T(json, "count", &count);
  
  Json json_indices;
  if (try_load_T(json, "indices", &json_indices)) {
    indices.fill(json_indices);
  }
  Json json_values;
  if (try_load_T(json, "values", &json_values)) {
    values.fill(json_values);
  }
}
void Accessor::Sparse::Indices::fill(Json json) {
  try_load_T(json, "bufferView", &buffer_view);
  try_load_T(json, "byteOffset", &byte_offset);
  try_load_T(json, "componentType", &component_type);
}
void Accessor::Sparse::Values::fill(Json json) {
  try_load_T(json, "bufferView", &buffer_view);
  try_load_T(json, "byteOffset", &byte_offset);
}


} // namespace glTF
} // namespace Sol
