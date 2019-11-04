#include "image/bmp.hpp"

#include <array>
#include <cstdlib>
#include <cstring>
#include <string_view>
#include <vector>

#include "log.hpp"
#include "util/util.hpp"

bool specula::image::write_bmp(
    const std::string_view &file, const Size<std::size_t> &resolution,
    const std::vector<std::array<double, 3>> &buffer) {
  FILE *out;
  int filesize = 54 + 3 * resolution.w * resolution.h;
  std::uint8_t *img =
      (std::uint8_t *)std::malloc(3 * resolution.w * resolution.h);
  std::memset(img, 0, 3 * resolution.w * resolution.h);
  for (std::size_t i = 0; i < resolution.w; ++i) {
    for (std::size_t j = 0; j < resolution.h; ++j) {
      std::size_t x = i;
      std::size_t y = (resolution.h - 1) - j;
      img[(x + y * resolution.w) * 3 + 2] =
          static_cast<uint8_t>(buffer[i + j * resolution.w][0] * 0xff);
      img[(x + y * resolution.w) * 3 + 1] =
          static_cast<uint8_t>(buffer[i + j * resolution.w][1] * 0xff);
      img[(x + y * resolution.w) * 3 + 0] =
          static_cast<uint8_t>(buffer[i + j * resolution.w][2] * 0xff);
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

  bmpinfoheader[4] = (unsigned char)(resolution.w);
  bmpinfoheader[5] = (unsigned char)(resolution.w >> 8);
  bmpinfoheader[6] = (unsigned char)(resolution.w >> 16);
  bmpinfoheader[7] = (unsigned char)(resolution.w >> 24);
  bmpinfoheader[8] = (unsigned char)(resolution.h);
  bmpinfoheader[9] = (unsigned char)(resolution.h >> 8);
  bmpinfoheader[10] = (unsigned char)(resolution.h >> 16);
  bmpinfoheader[11] = (unsigned char)(resolution.h >> 24);

  out = fopen(file.data(), "wb");
  fwrite(bmpfileheader, 1, 14, out);
  fwrite(bmpinfoheader, 1, 40, out);
  for (int i = 0; i < resolution.h; i++) {
    fwrite(img + (resolution.w * (resolution.h - i - 1) * 3), 3, resolution.w,
           out);
    fwrite(bmppad, 1, (4 - (resolution.w * 3) % 4) % 4, out);
  }
  free(img);
  fclose(out);

  LINFO("Wrote image to \"{}\"", file);
  return true;
}
