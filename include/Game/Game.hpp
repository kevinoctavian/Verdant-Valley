#pragma once

#include <memory>

#include "Renderer/VertexArray.hpp"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/ElementBuffer.hpp"

namespace VV::Common {
class VerdantValleyWindow;
}

namespace VV::Game {
class Game {
private:
  Common::VerdantValleyWindow *_window;

  std::unique_ptr<Renderer::VertexArray> _VAO;
  std::unique_ptr<Renderer::VertexBuffer> _VBO;
  std::unique_ptr<Renderer::ElementBuffer> _EBO;

  unsigned char *_image;
  int _widthImg;
  int _heightImg;

  GLuint _texture;

public:
  Game(Common::VerdantValleyWindow *window);
  ~Game();

  // Processing input
  /*
   * Handling the key process from GLFW/window
   */
  void KeyProcess(int key, int action, int mods);
  /*
   * Handling the mouse prosses from GLFW/window
   */
  void CursorProcess(double xPos, double ypos);
  void ButtonProcess(int button, int action, int mods);

  // processing updating and rendering
  void Update(float dt);
  void Render();
};
} // namespace VV::Game
