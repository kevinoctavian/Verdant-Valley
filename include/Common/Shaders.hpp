#pragma once

#include "glad/gl.h"

#include "glm/glm.hpp"

#include <string>

namespace VV::Common {
class Shader {
private:
  GLenum ID;

public:
  Shader(const std::string &vertexShader, const std::string &fragmentShader);
  ~Shader();

  void UseShader();

  void SetBool(const char *name, bool value);
  void SetInt(const char *name, int value);
  void SetFloat(const char *name, float value);

  void SetMat4f(const char *name, const glm::mat4x4 &mat);
  void SetVec2f(const char *name, const glm::vec2 &vec);
  void SetVec3f(const char *name, const glm::vec3 &vec);
  void SetVec4f(const char *name, const glm::vec4 &vec);
};
} // namespace VV::Common
