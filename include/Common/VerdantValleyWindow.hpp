#pragma once

#define GLFW_INCLUDE_NONE
#include "Shaders.hpp"
#include "GLFW/glfw3.h"

#include "Game/Game.hpp"
#include <memory>

namespace VV::Common {
class VerdantValleyWindow {
private:
  GLFWwindow *_window;
  int _width, _height;

  std::unique_ptr<Shader> _shader;

  GLfloat _lastFrameTime;
  float _deltaTime;
  std::unique_ptr<VV::Game::Game> _game;

private:
  static void CursorPosCallback(GLFWwindow *window, double xPos, double yPos);
  static void MouseButtonCallback(GLFWwindow *window, int button, int action,
                                  int mods);
  static void KeyboardCallback(GLFWwindow *window, int key, int scancode,
                               int action, int mods);
  static void FrameSizeCallback(GLFWwindow *window, int width, int height);

public:
  VerdantValleyWindow(int width, int height);
  ~VerdantValleyWindow();

  void Start();

  void SetVSync(int value) { glfwSwapInterval(value); }

  // Getter Area

  int GetWidth() { return _width; }
  int GetHeight() { return _height; }

  VV::Game::Game *GetGame() { return _game.get(); }
  Shader *GetShader() { return _shader.get(); }
  // Setter Area

  void SetWidth(int width) { _width = width; }
  void SetHeight(int height) { _height = height; }
};
} // namespace VV::Common
