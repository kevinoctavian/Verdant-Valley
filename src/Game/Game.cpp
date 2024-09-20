#include "Game/Game.hpp"
#include "Common/VerdantValleyWindow.hpp"
#include "Common/TextureLoader.hpp"

#include "glad/gl.h"
#include "Logs/Logs.hpp"

using namespace VV::Game;

Game::Game(VV::Common::VerdantValleyWindow *window) : _window(window) {
  _VAO.reset(new Renderer::VertexArray());
  _VAO->Bind();

  int y = 0, x = 9;

  float atlasXX = (float)(x * 16) / 160;       // top left
  float atlasXY = (float)((x + 1) * 16) / 160; // top right
  float atlasYX = (float)(y * 16) / 160;       // bottom left
  float atlasYY = (float)((y + 1) * 16) / 160; //  bottom right

  VV_INFO("atlas (XX {}, YY {}) (XY {}. YX {})", atlasXX, atlasYY, atlasXY,
          atlasYX)

  // atlas (XX 0, YY 1) (XY 0.1. YX 0.9)

  float vertices[] = {
      -0.5f, 0.9f,  0.0f, 0.0f,    0.0f, // Top-left
      0.5f,  0.9f,  0.0f, 1.0f,    0.0f, // Top-right
      0.5f,  0.1f,  0.0f, 1.0f,    1.0f, // Bottom-right
      -0.5f, 0.1f,  0.0f, 0.0f,    1.0f, // Bottom left

      -0.5f, 0.0f,  0.0f, atlasYX, atlasXX, // Top-left
      0.5f,  0.0f,  0.0f, atlasYY, atlasXX, // Top-right
      0.5f,  -0.9f, 0.0f, atlasYY, atlasXY, // Bottom-right
      -0.5f, -0.9f, 0.0f, atlasYX, atlasXY  // Bottom left
  };

  _VBO.reset(new Renderer::VertexBuffer(vertices, sizeof(vertices)));

  unsigned int indices[] = {
      0, 1, 2, //
      2, 3, 0, //
      4, 5, 6, //
      6, 7, 4  //
  };

  _EBO.reset(new Renderer::ElementBuffer(indices, sizeof(indices)));

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  _window->GetShader()->UseShader();
  _window->GetShader()->SetInt("Texture1", 0);
  _window->GetShader()->SetVec4f("Colors", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  _image = nullptr;
  _widthImg = _heightImg = 0;

  Common::TextureLoader::LoadPng("assets/Dungeon_Tileset.png", &_image,
                                 &_widthImg, &_heightImg);

  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glActiveTexture(GL_TEXTURE0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _widthImg, _heightImg, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, _image);

  _VAO->UnBind();
  _VBO->UnBind();
  _EBO->UnBind();
}
Game::~Game() {}

void Game::KeyProcess(int key, int action, int mods) {
  VV_INFO("Key Pressed key = {}, action = {}, mods = {}", key, action, mods);
}
void Game::CursorProcess(double xPos, double yPos) {}
void Game::ButtonProcess(int button, int action, int mods) {
  VV_INFO("Mouse clicked btn = {}, action = {}, mods = {}", button, action,
          mods);
}

void Game::Update(float dt) {}
void Game::Render() {
  _window->GetShader()->UseShader();

  _VAO->Bind();
  glDrawElements(GL_TRIANGLES, 6 * 2, GL_UNSIGNED_INT, 0);
}
