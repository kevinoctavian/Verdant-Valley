#include "Common/VerdantValleyWindow.hpp"

#include "Logs/LogManager.hpp"
#include "Logs/Logs.hpp"

int main() {
  VV::LogManager logs;

  VV_INFO("Inital Verdant Valley");

  VV::Common::VerdantValleyWindow *game =
      new VV::Common::VerdantValleyWindow(800, 600);
  game->Start();
  return 0;
}
