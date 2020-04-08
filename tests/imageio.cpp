#include <specula/core/imageio.hpp>
#include <specula/global.hpp>

#include <catch2/catch.hpp>

using namespace specula;

TEST_CASE("ImageIO") {
  Point2i res(16, 29);
  std::vector<Float> pixels(3 * res[0] * res[1]);
  for (int y = 0; y < res[1]; ++y) {
    for (int x = 0; x < res[0]; ++x) {
      int offset = 3 * (y * res[0] + x);
      pixels[offset] = Float(x) / Float(res[0] - 1);
      pixels[offset + 1] = Float(y) / Float(res[1] - 1);
      pixels[offset + 2] = 0.0f;
    }
  }
  SECTION("PPM") {
    write_image("out.ppm", &pixels[0], Bounds2i({0, 0}, res), res);
    Point2i read_res;
    auto read_pixels = read_image("out.ppm", &read_res);
    REQUIRE(read_pixels.get() != nullptr);
    REQUIRE(read_res == res);
    for (int y = 0; y < res[1]; ++y) {
      for (int x = 0; x < res[0]; ++x) {
        Float rgb[3];
        read_pixels[y * res[0] + x].to_rgb(rgb);
        for (int c = 0; c < 3; ++c) {
          REQUIRE(pixels[3 * (y * res[0] + x) + c] ==
                  Approx(rgb[c]).margin(0.005));
        }
      }
    }
  }
  SECTION("PNG") {
    write_image("out.png", &pixels[0], Bounds2i({0, 0}, res), res);
    Point2i read_res;
    auto read_pixels = read_image("out.png", &read_res);
    REQUIRE(read_pixels.get() != nullptr);
    REQUIRE(read_res == res);
    for (int y = 0; y < res[1]; ++y) {
      for (int x = 0; x < res[0]; ++x) {
        Float rgb[3];
        read_pixels[y * res[0] + x].to_rgb(rgb);
        for (int c = 0; c < 3; ++c) {
          REQUIRE(pixels[3 * (y * res[0] + x) + c] ==
                  Approx(rgb[c]).margin(0.005));
        }
      }
    }
  }
  SECTION("JPEG") {
    write_image("out.jpg", &pixels[0], Bounds2i({0, 0}, res), res);
    Point2i read_res;
    auto read_pixels = read_image("out.jpg", &read_res);
    REQUIRE(read_pixels.get() != nullptr);
    REQUIRE(read_res == res);
    for (int y = 0; y < res[1]; ++y) {
      for (int x = 0; x < res[0]; ++x) {
        Float rgb[3];
        read_pixels[y * res[0] + x].to_rgb(rgb);
        for (int c = 0; c < 3; ++c) {
          REQUIRE(pixels[3 * (y * res[0] + x) + c] ==
                  Approx(rgb[c]).margin(0.02));
        }
      }
    }
  }
  // SECTION("EXR") {
    // write_image("out.exr", &pixels[0], Bounds2i({0, 0}, res), res);
    // Point2i read_res;
    // auto read_pixels = read_image("out.exr", &read_res);
    // REQUIRE(read_pixels.get() != nullptr);
    // REQUIRE(read_res == res);
    // for (int y = 0; y < res[1]; ++y) {
      // for (int x = 0; x < res[0]; ++x) {
        // Float rgb[3];
        // read_pixels[y * res[0] + x].to_rgb(rgb);
        // for (int c = 0; c < 3; ++c) {
          // REQUIRE(pixels[3 * (y * res[0] + x) + c] ==
                  // Approx(rgb[c]).margin(0.005));
        // }
      // }
    // }
  // }
}
