#include "image/jpeg.hpp"

#include <array>
#include <cstdlib>
#include <cstring>
#include <string_view>
#include <vector>

#include <jpeglib.h>

#include <glm/glm.hpp>

#include "log.hpp"

bool specula::image::write_jpeg(const std::string_view &file,
                                const glm::uvec2 &resolution,
                                const std::vector<glm::vec3> &buffer) {
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *out;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  if ((out = fopen(file.data(), "wb")) == NULL) {
    LERROR("Failed to open \"{}\" for writting", file);
    return false;
  }
  jpeg_stdio_dest(&cinfo, out);
  cinfo.image_width = resolution.x;
  cinfo.image_height = resolution.y;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;

  jpeg_set_defaults(&cinfo);
  jpeg_start_compress(&cinfo, TRUE);
  std::uint8_t *pix_buffer =
      (std::uint8_t *)std::malloc(cinfo.image_width * 3 * sizeof(std::uint8_t));
  std::uint8_t *row_pointer[1];
  row_pointer[0] = pix_buffer;
  while (cinfo.next_scanline < cinfo.image_height) {
    for (std::size_t x = 0; x < cinfo.image_width; ++x) {
      pix_buffer[x * 3 + 0] = static_cast<std::uint8_t>(
          buffer[cinfo.next_scanline * cinfo.image_height + x].r * 0xff);
      pix_buffer[x * 3 + 1] = static_cast<std::uint8_t>(
          buffer[cinfo.next_scanline * cinfo.image_height + x].g * 0xff);
      pix_buffer[x * 3 + 2] = static_cast<std::uint8_t>(
          buffer[cinfo.next_scanline * cinfo.image_height + x].b * 0xff);
    }
    (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }
  jpeg_finish_compress(&cinfo);
  fclose(out);
  jpeg_destroy_compress(&cinfo);
  free(pix_buffer);
  LINFO("Wrote image to \"{}\"", file);
  return false;
}
