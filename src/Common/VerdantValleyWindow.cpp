#include "Common/VerdantValleyWindow.hpp"
#include "Logs/Logs.hpp"

// auto generated vertexShader and fragmentShader
#include "vertex_shader.h"
#include "fragment_shader.h"

using namespace VV::Common;

VerdantValleyWindow::VerdantValleyWindow(int width, int height)
    : _width(width), _height(height), _shader(nullptr), _lastFrameTime(0.0f),
      _deltaTime(0.0f) {
  if (!glfwInit()) {
    VV_ERROR("Failed to initlize Window exit 1")
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window =
      glfwCreateWindow(_width, _height, "Verdant Valley", nullptr, nullptr);
  if (!_window) {
    VV_ERROR("Failed to create window exit 1")
    exit(1);
  }

  glfwMakeContextCurrent(_window);

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    VV_ERROR("Failed to initlize OpenGL exit 1")
    exit(1);
  }

  // set VerdantValleyWindow as window user pointer that can used by callback
  glfwSetWindowUserPointer(_window, this);

  // Setup input callback
  glfwSetFramebufferSizeCallback(_window,
                                 &VerdantValleyWindow::FrameSizeCallback);
  glfwSetKeyCallback(_window, &VerdantValleyWindow::KeyboardCallback);
  glfwSetMouseButtonCallback(_window,
                             &VerdantValleyWindow::MouseButtonCallback);
  glfwSetCursorPosCallback(_window, &VerdantValleyWindow::CursorPosCallback);

  _shader.reset(new Shader(
      std::string((const char *)g_vertex_shader_data, g_vertex_shader_data_len),
      std::string((const char *)g_fragment_shader_data,
                  g_fragment_shader_data_len)));

  _game.reset(new Game::Game(this));
  glfwSwapInterval(1);
}

VerdantValleyWindow::~VerdantValleyWindow() {
  glfwMakeContextCurrent(nullptr);
  glfwDestroyWindow(_window);
  glfwTerminate();
}

void VerdantValleyWindow::Start() {
  while (!glfwWindowShouldClose(_window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat currentFrameTime = glfwGetTime();
    _deltaTime = currentFrameTime - _lastFrameTime;
    _lastFrameTime = currentFrameTime;

    _game->Update(_deltaTime);
    _game->Render();

    glfwSwapBuffers(_window);
    glfwPollEvents();
  }
}

void VerdantValleyWindow::CursorPosCallback(GLFWwindow *window, double xPos,
                                            double yPos) {
  VerdantValleyWindow *vvWindow =
      (VerdantValleyWindow *)glfwGetWindowUserPointer(window);

  if (vvWindow)
    vvWindow->GetGame()->CursorProcess(xPos, yPos);
}

void VerdantValleyWindow::MouseButtonCallback(GLFWwindow *window, int button,
                                              int action, int mods) {
  VerdantValleyWindow *vvWindow =
      (VerdantValleyWindow *)glfwGetWindowUserPointer(window);

  if (vvWindow)
    vvWindow->GetGame()->ButtonProcess(button, action, mods);
}

void VerdantValleyWindow::KeyboardCallback(GLFWwindow *window, int key,
                                           int scancode, int action, int mods) {
  VerdantValleyWindow *vvWindow =
      (VerdantValleyWindow *)glfwGetWindowUserPointer(window);

  if (vvWindow)
    vvWindow->GetGame()->KeyProcess(key, action, mods);

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

void VerdantValleyWindow::FrameSizeCallback(GLFWwindow *window, int width,
                                            int height) {
  VerdantValleyWindow *vvWindow =
      (VerdantValleyWindow *)glfwGetWindowUserPointer(window);

  if (vvWindow) {
    vvWindow->SetWidth(width);
    vvWindow->SetHeight(height);
  }

  glViewport(0, 0, width, height);
}
