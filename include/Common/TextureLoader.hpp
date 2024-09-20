#pragma once

#include <string>

namespace VV::Common::TextureLoader {
bool LoadPng(const std::string &path, unsigned char **data, int *width,
             int *height);
} // namespace VV::Common::TextureLoader
