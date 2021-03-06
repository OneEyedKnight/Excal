#include "model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <unordered_map>
#include <vector>

#include "structs.h"

namespace Excal::Model
{
ModelData loadModel(
  const std::string& modelPath
) {
  tinyobj::attrib_t attrib;  // Holds positions, normals, and texture coordinates
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  if (!tinyobj::LoadObj(
        &attrib, &shapes, &materials,
        &warn, &err,
        modelPath.c_str()
      )
  ) {
    throw std::runtime_error(warn + err);
  }

  std::unordered_map<Vertex, uint32_t> uniqueVertices{};

  ModelData modelData;
  // Iterate over the shapes vertices and add them to the argument `modelData`
  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      Vertex vertex{};

      // Load arrays of floats into vectors
      vertex.pos = {
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
      };

      vertex.texCoord = {
            attrib.texcoords[2 * index.texcoord_index + 0],
        1.0-attrib.texcoords[2 * index.texcoord_index + 1] // Flip vertical coordinate
      };

      // Not handled by this model loader
      vertex.color  = {1.0f, 1.0f, 1.0f};
      vertex.normal = {1.0f, 1.0f, 1.0f};

      if (uniqueVertices.count(vertex) == 0) {
        uniqueVertices[vertex] = static_cast<uint32_t>(modelData.vertices.size());
        modelData.vertices.push_back(vertex);
      }

      modelData.indices.push_back(uniqueVertices[vertex]);
    }
  }

  return modelData;
}

Model createModel(
  const std::string& modelPath,
  const glm::vec3    position,
  const float        scale,
  const std::string& diffuseTexturePath,
  const std::string& normalTexturePath
) {
  auto modelData = loadModel(modelPath);

  return Model {
    modelData.indices,
    modelData.vertices,
    diffuseTexturePath,
    normalTexturePath,
    position,
    scale
  };
}
}
