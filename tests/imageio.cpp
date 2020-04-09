#include <specula/core/imageio.hpp>
#include <specula/global.hpp>

#include <catch2/catch.hpp>

#include <ghc/filesystem.hpp>
namespace fs {
using namespace ghc::filesystem;
using ifstream = ghc::filesystem::ifstream;
using ofstream = ghc::filesystem::ofstream;
using fstream = ghc::filesystem::fstream;
} // namespace fs

using namespace specula;

static void test_round_trip(const char *fn, bool gamma) {
  fs::path filepath = fn;
  Point2i res(16, 29);
  std::vector<Float> pixels(3 * res[0] * res[1]);
  for (int y = 0; y < res[1]; ++y) {
    for (int x = 0; x < res[0]; ++x) {
      int offset = 3 * (y * res[0] + x);
      pixels[offset] = Float(x) / Float(res[0] - 1);
      pixels[offset + 1] = Float(y) / Float(res[1] - 1);
      pixels[offset + 2] = -1.5f;
    }
  }
  write_image(fn, &pixels[0], Bounds2i({0, 0}, res), res);

  Point2i read_res;
  auto read_pixels = read_image(fn, &read_res);
  REQUIRE(read_pixels.get() != nullptr);
  REQUIRE(read_res == res);

  for (int y = 0; y < res[1]; ++y) {
    for (int x = 0; x < res[0]; ++x) {
      Float rgb[3];
      read_pixels[y * res[0] + x].to_rgb(rgb);

      for (int c = 0; c < 3; ++c) {
        if (gamma)
          rgb[c] = inverse_gamma_correct(rgb[c]);

        float wrote = pixels[3 * (y * res[0] + x) + c];
        float delta = wrote - rgb[c];
        if (filepath.extension() == ".exr") {
          if (c == 2)
            REQUIRE(0.0 == delta);
          else
            REQUIRE(std::abs(delta) < 0.001);
        } else {
          if (c == 2)
            REQUIRE(std::abs(rgb[c]) < 0.001);
          else {
            REQUIRE(std::abs(delta) < 0.02);
          }
        }
      }
    }
  }
}

TEST_CASE("ImageIO") {
  SECTION("PNG") { test_round_trip("test.png", true); }
  SECTION("BMP") { test_round_trip("test.bmp", true); }
  SECTION("TGA") { test_round_trip("test.tga", true); }
  SECTION("JPEG") { test_round_trip("test.jpg", true); }
  // SECTION("HDR") {
  // test_round_trip("test.hdr", false);
  // }
  SECTION("EXR") { test_round_trip("test.exr", false); }
}
