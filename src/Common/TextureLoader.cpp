#include "Common/TextureLoader.hpp"
#include "Logs/Logs.hpp"

#include "png.h"

bool VV::Common::TextureLoader::LoadPng(const std::string &path,
                                        unsigned char **data, int *width,
                                        int *height) {
  FILE *pngFile = fopen(path.c_str(), "rb");
  if (!pngFile) {
    VV_WARN("{} file path not found!", path.c_str())
    return false;
  }

  png_structp png =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png) {
    VV_ERROR("could't create png reader")
    fclose(pngFile);
    return false;
  }

  png_infop pngInfo = png_create_info_struct(png);
  if (!pngInfo) {
    VV_ERROR("Could't create png info struct")
    png_destroy_read_struct(&png, &pngInfo, nullptr);
    fclose(pngFile);
    return false;
  }

  if (setjmp(png_jmpbuf(png))) {
    VV_ERROR("An error occurred while reading the PNG file")
    png_destroy_read_struct(&png, &pngInfo, NULL);
    fclose(pngFile);
    return false;
  }

  VV_INFO("init png")
  png_init_io(png, pngFile);

  VV_INFO("read the png")
  png_read_png(png, pngInfo, PNG_TRANSFORM_IDENTITY, nullptr);

  VV_INFO("Set width height of image")
  *width = png_get_image_width(png, pngInfo);
  *height = png_get_image_height(png, pngInfo);
  png_byte colorType = png_get_color_type(png, pngInfo);
  png_byte bitDepth = png_get_bit_depth(png, pngInfo);

  VV_INFO("Image size {}x{}", *width, *height);

  if (colorType == PNG_COLOR_TYPE_RGB) {
    VV_INFO("image has RGB color type")
  } else if (colorType == PNG_COLOR_TYPE_RGBA) {
    VV_INFO("image has RGBA color type")
  } else {
    VV_INFO("unknown colortype {}", colorType)
  }

  /*// Handle transparency if necessary*/
  /*if (bitDepth == 16)*/
  /*  png_set_strip_16(png);*/
  /*if (colorType == PNG_COLOR_TYPE_PALETTE)*/
  /*  png_set_palette_to_rgb(png);*/
  /*if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)*/
  /*  png_set_expand_gray_1_2_4_to_8(png);*/
  /*if (png_get_valid(png, pngInfo, PNG_INFO_tRNS))*/
  /*  png_set_tRNS_to_alpha(png);*/
  /*if (colorType == PNG_COLOR_TYPE_RGB || colorType == PNG_COLOR_TYPE_GRAY ||*/
  /*    colorType == PNG_COLOR_TYPE_PALETTE)*/
  /*  png_set_filler(png, 0xFF, PNG_FILLER_AFTER);*/
  /**/
  /*png_read_update_info(png, pngInfo);*/

  if (*data) {
    VV_INFO("try to free data if exist")
    free(*data);
  }

  VV_INFO("allocate data and temp data")
  png_size_t rowBytes = png_get_rowbytes(png, pngInfo);
  size_t imageSize = rowBytes * (*height);

  *data = static_cast<unsigned char *>(malloc(imageSize));
  if (!*data) {
    VV_ERROR("Could not allocate memory for image data")
    png_destroy_read_struct(&png, &pngInfo, NULL);
    fclose(pngFile);
    return false;
  }

  png_bytep *rowPointers = png_get_rows(png, pngInfo);
  for (int y = 0; y < *height; y++) {
    memcpy(*data + y * rowBytes, rowPointers[y], rowBytes);
  }

  png_destroy_read_struct(&png, &pngInfo, nullptr);
  fclose(pngFile);
  return true;
}
