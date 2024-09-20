set(COMMON_SOURCE Common/Shader.cpp Common/VerdantValleyWindow.cpp
                  Common/TextureLoader.cpp)

set(LOG_SOURCE Logs/LogManager.cpp)

set(RENDERER_SOURCE Renderer/VertexArray.cpp Renderer/VertexBuffer.cpp
                    Renderer/ElementBuffer.cpp)

set(GAME_SOURCE Game/Game.cpp)

add_executable(${PROJECT_NAME} main.cpp ${COMMON_SOURCE} ${LOG_SOURCE}
                               ${RENDERER_SOURCE} ${GAME_SOURCE})
