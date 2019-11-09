#include "image/bmp.hpp"

#include <array>
#include <cstdlib>
#include <cstring>
#include <string_view>
#include <vector>

#include <glm/glm.hpp>

#include "log.hpp"

bool specula::image::write_bmp(const std::string_view &file,
                               const glm::uvec2 &resolution,
                               const std::vector<glm::vec3> &buffer) {
  FILE *out;
  int filesize = 54 + 3 * resolution.x * resolution.y;
  std::uint8_t *img =
      (std::uint8_t *)std::malloc(3 * resolution.x * resolution.y);
  std::memset(img, 0, 3 * resolution.x * resolution.y);
  for (std::size_t i = 0; i < resolution.x; ++i) {
    for (std::size_t j = 0; j < resolution.y; ++j) {
      std::size_t x = i;
      std::size_t y = (resolution.y - 1) - j;
      img[(x + y * resolution.x) * 3 + 2] =
          static_cast<uint8_t>(buffer[i + j * resolution.x].r * 0xff);
      img[(x + y * resolution.x) * 3 + 1] =
          static_cast<uint8_t>(buffer[i + j * resolution.x].g * 0xff);
      img[(x + y * resolution.x) * 3 + 0] =
          static_cast<uint8_t>(buffer[i + j * resolution.x].b * 0xff);
    }
  }

  unsigned char bmpfileheader[14] = {'B', 'M', 0, 0,  0, 0, 0,
                                     0,   0,   0, 54, 0, 0, 0};
  unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0,  0,
                                     0,  0, 0, 0, 1, 0, 24, 0};
  unsigned char bmppad[3] = {0, 0, 0};

  bmpfileheader[2] = (unsigned char)(filesize);
  bmpfileheader[3] = (unsigned char)(filesize >> 8);
  bmpfileheader[4] = (unsigned char)(filesize >> 16);
  bmpfileheader[5] = (unsigned char)(filesize >> 24);

  bmpinfoheader[4] = (unsigned char)(resolution.x);
  bmpinfoheader[5] = (unsigned char)(resolution.x >> 8);
  bmpinfoheader[6] = (unsigned char)(resolution.x >> 16);
  bmpinfoheader[7] = (unsigned char)(resolution.x >> 24);
  bmpinfoheader[8] = (unsigned char)(resolution.y);
  bmpinfoheader[9] = (unsigned char)(resolution.y >> 8);
  bmpinfoheader[10] = (unsigned char)(resolution.y >> 16);
  bmpinfoheader[11] = (unsigned char)(resolution.y >> 24);

  out = fopen(file.data(), "wb");
  fwrite(bmpfileheader, 1, 14, out);
  fwrite(bmpinfoheader, 1, 40, out);
  for (std::size_t i = 0; i < resolution.y; i++) {
    fwrite(img + (resolution.x * (resolution.y - i - 1) * 3), 3, resolution.x,
           out);
    fwrite(bmppad, 1, (4 - (resolution.x * 3) % 4) % 4, out);
  }
  free(img);
  fclose(out);

  LINFO("Wrote image to \"{}\"", file);
  return true;
}
