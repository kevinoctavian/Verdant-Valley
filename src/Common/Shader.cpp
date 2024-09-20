#include "Common/Shaders.hpp"
#include "Logs/Logs.hpp"

#include "glm/gtc/type_ptr.hpp"

#include <vector>

using namespace VV::Common;

Shader::Shader(const std::string &vertexShader,
               const std::string &fragmentShader) {
  GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  GLint glResult = GL_FALSE;
  int infoLogLength;

  char const *vertexSourcePointer = vertexShader.c_str();
  glShaderSource(vertexShaderID, 1, &vertexSourcePointer, nullptr);
  glCompileShader(vertexShaderID);

  glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &glResult);
  glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr,
                       &vertexShaderErrorMessage[0]);
    VV_ERROR("Vertex Error {}", &vertexShaderErrorMessage[0]);
  }

  char const *fragmentSourcePointer = fragmentShader.c_str();
  glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, nullptr);
  glCompileShader(fragmentShaderID);

  glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &glResult);
  glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, nullptr,
                       &fragmentShaderErrorMessage[0]);
    VV_ERROR("Fragment Error {}", &fragmentShaderErrorMessage[0]);
  }

  ID = glCreateProgram();
  glAttachShader(ID, vertexShaderID);
  glAttachShader(ID, fragmentShaderID);
  glLinkProgram(ID);

  glGetProgramiv(ID, GL_LINK_STATUS, &glResult);
  glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> programErrorMessage(infoLogLength + 1);
    glGetProgramInfoLog(ID, infoLogLength, NULL, &programErrorMessage[0]);
    VV_ERROR("Program Error {}", &programErrorMessage[0]);
  }

  glDetachShader(ID, vertexShaderID);
  glDetachShader(ID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
}

Shader::~Shader() { glDeleteProgram(ID); }

void Shader::UseShader() { glUseProgram(ID); }

void Shader::SetBool(const char *name, bool value) {
  glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetInt(const char *name, int value) {
  glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetFloat(const char *name, float value) {
  glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetMat4f(const char *name, const glm::mat4x4 &mat) {
  glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE,
                     glm::value_ptr(mat));
}

void Shader::SetVec2f(const char *name, const glm::vec2 &vec) {
  glUniform2f(glGetUniformLocation(ID, name), vec.x, vec.y);
}

void Shader::SetVec3f(const char *name, const glm::vec3 &vec) {
  glUniform3f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z);
}

void Shader::SetVec4f(const char *name, const glm::vec4 &vec) {
  glUniform4f(glGetUniformLocation(ID, name), vec.x, vec.y, vec.z, vec.w);
}
