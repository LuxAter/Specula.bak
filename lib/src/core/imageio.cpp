#include "specula/core/imageio.hpp"
#include "core/spectrum/rgb.hpp"
#include "global/functions.hpp"
#include "specula/core/spectrum.hpp"

#include <ghc/fs_std.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <ImfRgba.h>
#include <ImfRgbaFile.h>
#include <stb_image.h>
#include <stb_image_write.h>

std::unique_ptr<specula::RGBSpectrum[]>
specula::read_image(const std::string &name, Point2i *resolution) {
  fs::path filepath(name);
  if (filepath.extension() == ".exr") {
    return std::unique_ptr<RGBSpectrum[]>(
        read_image_exr(filepath, &resolution->x, &resolution->y));
  } else if (filepath.extension() == ".png") {
    return std::unique_ptr<RGBSpectrum[]>(
        read_image_png(filepath, &resolution->x, &resolution->y));
  } else if (filepath.extension() == ".bmp") {
    return std::unique_ptr<RGBSpectrum[]>(
        read_image_bmp(filepath, &resolution->x, &resolution->y));
  } else if (filepath.extension() == ".tga") {
    return std::unique_ptr<RGBSpectrum[]>(
        read_image_tga(filepath, &resolution->x, &resolution->y));
  } else if (filepath.extension() == ".jpg") {
    return std::unique_ptr<RGBSpectrum[]>(
        read_image_jpg(filepath, &resolution->x, &resolution->y));
  } else if (filepath.extension() == ".hdr") {
    return std::unique_ptr<RGBSpectrum[]>(
        read_image_hdr(filepath, &resolution->x, &resolution->y));
  }
  LERROR("Unable to load image stored in format \"{}\" for filename \"{}\"",
         filepath.extension(), filepath);
  return nullptr;
}

bool specula::write_image(const std::string &name, const Float *rgb,
                          const Bounds2i &output_bounds,
                          const Point2i &total_resolution) {
  fs::path filepath(name);
  Vector2i resolution = output_bounds.diagonal();
  if (filepath.extension() == ".exr") {
    return write_image_exr(filepath, rgb, resolution.x, resolution.y,
                           total_resolution.x, total_resolution.y,
                           output_bounds.p_min.x, output_bounds.p_min.y);
  } else if (filepath.extension() == ".hdr") {
    std::unique_ptr<float[]> rgbf(new float[3 * resolution.x * resolution.y]);
    for (std::size_t i = 0; i < resolution.x * resolution.y; ++i) {
      rgbf[i] = static_cast<float>(rgb[i]);
      rgbf[i + 1] = static_cast<float>(rgb[i + 1]);
      rgbf[i + 2] = static_cast<float>(rgb[i + 2]);
    }
    return write_image_hdr(filepath, rgbf.get(), resolution.x, resolution.y,
                           total_resolution.x, total_resolution.y,
                           output_bounds.p_min.x, output_bounds.p_min.y);
  } else {
    std::unique_ptr<std::uint8_t[]> rgb8(
        new std::uint8_t[3 * resolution.x * resolution.y]);
    std::uint8_t *dst = rgb8.get();
    for (int y = 0; y < resolution.y; ++y) {
      for (int x = 0; x < resolution.x; ++x) {
        dst[0] = static_cast<std::uint8_t>(clamp(
            255.0f * gamma_correct(rgb[3 * (y * resolution.x + x) + 0]) + 0.5f,
            0.0f, 255.0f));
        dst[1] = static_cast<std::uint8_t>(clamp(
            255.0f * gamma_correct(rgb[3 * (y * resolution.x + x) + 1]) + 0.5f,
            0.0f, 255.0f));
        dst[2] = static_cast<std::uint8_t>(clamp(
            255.0f * gamma_correct(rgb[3 * (y * resolution.x + x) + 2]) + 0.5f,
            0.0f, 255.0f));
        dst += 3;
      }
    }
    if (filepath.extension() == ".png") {
      return write_image_png(filepath, rgb8.get(), resolution.x, resolution.y,
                             total_resolution.x, total_resolution.y,
                             output_bounds.p_min.x, output_bounds.p_min.y);
    } else if (filepath.extension() == ".bmp") {
      return write_image_bmp(filepath, rgb8.get(), resolution.x, resolution.y,
                             total_resolution.x, total_resolution.y,
                             output_bounds.p_min.x, output_bounds.p_min.y);
    } else if (filepath.extension() == ".tga") {
      return write_image_tga(filepath, rgb8.get(), resolution.x, resolution.y,
                             total_resolution.x, total_resolution.y,
                             output_bounds.p_min.x, output_bounds.p_min.y);
    } else if (filepath.extension() == ".jpg") {
      return write_image_jpg(filepath, rgb8.get(), resolution.x, resolution.y,
                             total_resolution.x, total_resolution.y,
                             output_bounds.p_min.x, output_bounds.p_min.y);
    } else {
      LERROR("Can't determine image file type from suffix of filename \"{}\"",
             filepath.c_str());
    }
  }
  return false;
}

specula::RGBSpectrum *specula::read_image_exr(const fs::path &filepath,
                                              int *width, int *height,
                                              Bounds2i *data_window,
                                              Bounds2i *display_window) {
  try {
    Imf::RgbaInputFile file(filepath.c_str());
    Imath::Box2i dw = file.dataWindow();
    if (data_window) {
      *data_window = {{dw.min.x, dw.min.y}, {dw.max.x + 1, dw.max.y + 1}};
    }
    if (display_window) {
      Imath::Box2i dispw = file.displayWindow();
      *display_window = {{dispw.min.x, dispw.min.y},
                         {dispw.max.x + 1, dispw.max.y + 1}};
    }
    *width = dw.max.x - dw.min.x + 1;
    *height = dw.max.y - dw.min.y + 1;

    std::vector<Imf::Rgba> pixels(*width * *height);
    file.setFrameBuffer(&pixels[0] - dw.min.x - dw.min.y * *width, 1, *width);
    file.readPixels(dw.min.y, dw.max.y);

    RGBSpectrum *ret = new RGBSpectrum[*width * *height];
    for (int i = 0; i < *width * *height; ++i) {
      Float frgb[3] = {pixels[i].r, pixels[i].g, pixels[i].b};
      ret[i] = RGBSpectrum::from_rgb(frgb);
    }
    LINFO("Read EXR image {} ({} x {})", filepath, *width, *height);
    return ret;
  } catch (const std::exception &e) {
    LERROR("Unable ro read image file \"{}\": {}", filepath.c_str(), e.what());
  }
  return nullptr;
}
specula::RGBSpectrum *specula::read_image_png(const fs::path &filepath,
                                              int *width, int *height) {
  int n;
  stbi_ldr_to_hdr_scale(1.0f);
  stbi_ldr_to_hdr_gamma(1.0f);
  float *data = stbi_loadf(filepath.c_str(), width, height, &n, 3);
  if (data == nullptr) {
    LERROR("Unable to read image file \"{}\": {}", filepath.c_str(),
           stbi_failure_reason());
    return nullptr;
  }
  RGBSpectrum *ret = new RGBSpectrum[*width * *height];
  float *src = data;
  for (std::size_t y = 0; y < *height; ++y) {
    for (std::size_t x = 0; x < *width; ++x, src += 3) {
      ret[y * *width + x] = RGBSpectrum::from_rgb(src);
    }
  }
  free(data);
  LINFO("Read PNG image {} ({} x {})", filepath.c_str(), *width, *height);
  return ret;
}
specula::RGBSpectrum *specula::read_image_bmp(const fs::path &filepath,
                                              int *width, int *height) {
  int n;
  stbi_ldr_to_hdr_scale(1.0f);
  stbi_ldr_to_hdr_gamma(1.0f);
  float *data = stbi_loadf(filepath.c_str(), width, height, &n, 3);
  if (data == nullptr) {
    LERROR("Unable to read image file \"{}\": {}", filepath.c_str(),
           stbi_failure_reason());
    return nullptr;
  }
  RGBSpectrum *ret = new RGBSpectrum[*width * *height];
  float *src = data;
  for (std::size_t y = 0; y < *height; ++y) {
    for (std::size_t x = 0; x < *width; ++x, src += 3) {
      ret[y * *width + x] = RGBSpectrum::from_rgb(src);
    }
  }
  free(data);
  LINFO("Read BMP image {} ({} x {})", filepath.c_str(), *width, *height);
  return ret;
}
specula::RGBSpectrum *specula::read_image_tga(const fs::path &filepath,
                                              int *width, int *height) {
  int n;
  stbi_ldr_to_hdr_scale(1.0f);
  stbi_ldr_to_hdr_gamma(1.0f);
  float *data = stbi_loadf(filepath.c_str(), width, height, &n, 3);
  if (data == nullptr) {
    LERROR("Unable to read image file \"{}\": {}", filepath.c_str(),
           stbi_failure_reason());
    return nullptr;
  }
  RGBSpectrum *ret = new RGBSpectrum[*width * *height];
  float *src = data;
  for (std::size_t y = 0; y < *height; ++y) {
    for (std::size_t x = 0; x < *width; ++x, src += 3) {
      ret[y * *width + x] = RGBSpectrum::from_rgb(src);
    }
  }
  free(data);
  LINFO("Read TGA image {} ({} x {})", filepath.c_str(), *width, *height);
  return ret;
}
specula::RGBSpectrum *specula::read_image_jpg(const fs::path &filepath,
                                              int *width, int *height) {
  int n;
  stbi_ldr_to_hdr_scale(1.0f);
  stbi_ldr_to_hdr_gamma(1.0f);
  float *data = stbi_loadf(filepath.c_str(), width, height, &n, 3);
  if (data == nullptr) {
    LERROR("Unable to read image file \"{}\": {}", filepath.c_str(),
           stbi_failure_reason());
    return nullptr;
  }
  RGBSpectrum *ret = new RGBSpectrum[*width * *height];
  float *src = data;
  for (std::size_t y = 0; y < *height; ++y) {
    for (std::size_t x = 0; x < *width; ++x, src += 3) {
      ret[y * *width + x] = RGBSpectrum::from_rgb(src);
    }
  }
  free(data);
  LINFO("Read JPG image {} ({} x {})", filepath.c_str(), *width, *height);
  return ret;
}
specula::RGBSpectrum *specula::read_image_hdr(const fs::path &filepath,
                                              int *width, int *height) {
  int n;
  stbi_hdr_to_ldr_scale(1.0f);
  stbi_hdr_to_ldr_gamma(1.0f);
  float *data = stbi_loadf(filepath.c_str(), width, height, &n, 3);
  if (data == nullptr) {
    LERROR("Unable to read image file \"{}\": {}", filepath.c_str(),
           stbi_failure_reason());
    return nullptr;
  }
  RGBSpectrum *ret = new RGBSpectrum[*width * *height];
  float *src = data;
  for (std::size_t y = 0; y < *height; ++y) {
    for (std::size_t x = 0; x < *width; ++x, src += 3) {
      ret[y * *width + x] = RGBSpectrum::from_rgb(src);
    }
  }
  free(data);
  LINFO("Read HDR image {} ({} x {})", filepath.c_str(), *width, *height);
  return ret;
}

bool specula::write_image_exr(const fs::path &filepath, const Float *pixels,
                              int x_res, int y_res, int total_x_res,
                              int total_y_res, int x_offset, int y_offset) {
  Imf::Rgba *hrgba = new Imf::Rgba[x_res * y_res];
  for (int i = 0; i < x_res * y_res; ++i) {
    hrgba[i] = Imf::Rgba(pixels[3 * i], pixels[3 * i + 1], pixels[3 * i + 2]);
  }
  Imath::Box2i display_window(Imath::V2i(0, 0),
                              Imath::V2i(total_x_res - 1, total_y_res - 1));
  Imath::Box2i data_window(
      Imath::V2i(x_offset, y_offset),
      Imath::V2i(x_offset + x_res - 1, y_offset + y_res - 1));
  try {
    Imf::RgbaOutputFile file(filepath.c_str(), display_window, data_window,
                             Imf::WRITE_RGB);
    file.setFrameBuffer(hrgba - x_offset - y_offset * x_res, 1, x_res);
    file.writePixels(y_res);
    delete[] hrgba;
    return true;
  } catch (const std::exception &exc) {
    LERROR("Error writting \"{}\": {}", filepath.c_str(), exc.what());
    delete[] hrgba;
    return false;
  }
}
bool specula::write_image_png(const fs::path &filepath,
                              const std::uint8_t *pixels, int x_res, int y_res,
                              int, int, int, int) {
  if (stbi_write_png(filepath.c_str(), x_res, y_res, 3, pixels,
                     sizeof(std::uint8_t) * 3 * x_res) == 0) {
    LERROR("Error writting \"{}\"", filepath.c_str());
    return false;
  }
  return true;
}
bool specula::write_image_bmp(const fs::path &filepath,
                              const std::uint8_t *pixels, int x_res, int y_res,
                              int, int, int, int) {
  if (stbi_write_bmp(filepath.c_str(), x_res, y_res, 3, pixels) == 0) {
    LERROR("Error writting \"{}\"", filepath.c_str());
    return false;
  }
  return true;
}
bool specula::write_image_tga(const fs::path &filepath,
                              const std::uint8_t *pixels, int x_res, int y_res,
                              int, int, int, int) {
  if (stbi_write_tga(filepath.c_str(), x_res, y_res, 3, pixels) == 0) {
    LERROR("Error writting \"{}\"", filepath.c_str());
    return false;
  }
  return true;
}
bool specula::write_image_jpg(const fs::path &filepath,
                              const std::uint8_t *pixels, int x_res, int y_res,
                              int, int, int, int) {
  if (stbi_write_jpg(filepath.c_str(), x_res, y_res, 3, pixels, 100) == 0) {
    LERROR("Error writting \"{}\"", filepath.c_str());
    return false;
  }
  return true;
}
bool specula::write_image_hdr(const fs::path &filepath, const float *pixels,
                              int x_res, int y_res, int, int, int, int) {
  if (stbi_write_hdr(filepath.c_str(), x_res, y_res, 3, pixels) == 0) {
    LERROR("Error writting \"{}\"", filepath.c_str());
    return false;
  }
  return true;
}
