#include "image.hpp"

#include <math.h>

#include <fstream>
#include <string>
#include <vector>

#include <png.h>

#include <iostream>

specula::image::Image::Image() {}

specula::image::Image::Image(unsigned px_w, unsigned px_h)
    : width_(px_w),
      height_(px_h),
      size_(px_h * px_w),
      pixel_data_((px_w * px_h) * 3) {}

specula::image::Image::~Image() {}

void specula::image::Image::SetPixel(unsigned x, unsigned y, int red, int green,
                                     int blue) {
  unsigned pixel = (y * width_) + x;
  if (pixel < size_) {
    pixel *= 3;
    pixel_data_[pixel] = (red / 256.0);
    pixel_data_[pixel + 1] = (green / 256.0);
    pixel_data_[pixel + 2] = (blue / 256.0);
  }
}

void specula::image::Image::SetPixel(unsigned x, unsigned y, float red,
                                     float green, float blue) {
  unsigned pixel = (y * width_) + x;
  if (pixel < size_) {
    pixel *= 3;
    pixel_data_[pixel] = red;
    pixel_data_[pixel + 1] = green;
    pixel_data_[pixel + 2] = blue;
  }
}

void specula::image::Image::SetPixel(unsigned x, unsigned y, double red,
                                     double green, double blue) {
  unsigned pixel = (y * width_) + x;
  if (pixel < size_) {
    pixel *= 3;
    pixel_data_[pixel] = static_cast<float>(red);
    pixel_data_[pixel + 1] = static_cast<float>(green);
    pixel_data_[pixel + 2] = static_cast<float>(blue);
  }
}

void specula::image::Image::Fill(int red, int green, int blue) {
  float fred = (red / 256.0), fgreen = (green / 256.0), fblue = (blue / 256.0);
  for (unsigned x = 0; x < width_; ++x) {
    for (unsigned y = 0; y < height_; ++y) {
      SetPixel(x, y, fred, fgreen, fblue);
    }
  }
}
void specula::image::Image::Fill(float red, float green, float blue) {
  for (unsigned x = 0; x < width_; ++x) {
    for (unsigned y = 0; y < height_; ++y) {
      SetPixel(x, y, red, green, blue);
    }
  }
}
void specula::image::Image::Fill(double red, double green, double blue) {
  for (unsigned x = 0; x < width_; ++x) {
    for (unsigned y = 0; y < height_; ++y) {
      SetPixel(x, y, red, green, blue);
    }
  }
}

void specula::image::Image::Grad(double r1, double g1, double b1, double r2,
                                 double g2, double b2) {
  for (unsigned x = 0; x < width_; ++x) {
    for (unsigned y = 0; y < height_; ++y) {
      double a = (double)y / height_;
      double b = 1.0 - a;
      SetPixel(x, y, (a * r1) + (b * r2), (a * g1) + (b * g2),
               (a * b1) + (b * b2));
    }
  }
}

bool specula::image::Image::WriteBitmap(std::string file_name) {
  char padding_data[4] = {0x00, 0x00, 0x00, 0x00};
  unsigned padding = (4 - ((width_ * 3) % 4)) % 4;
  std::vector<unsigned char> byte_data = GetByteImg(BGR);

  unsigned info_size = (2 * sizeof(unsigned short)) + (9 * sizeof(unsigned));
  unsigned header_size = (3 * sizeof(unsigned short)) + (2 * sizeof(unsigned));

  unsigned i_size = info_size;
  unsigned i_width = width_;
  unsigned i_height = height_;
  unsigned short i_planes = 1;
  unsigned short i_bit_count = 24;
  unsigned i_compression = 0;
  unsigned i_size_image = (((i_width * 3) + 3) & 0x0000FFFC) * i_height;
  unsigned i_xpm = 0;
  unsigned i_ypm = 0;
  unsigned i_clru = 0;
  unsigned i_clri = 0;

  unsigned short h_type = 19778;
  unsigned h_size = header_size + info_size + i_size_image;
  unsigned short h_reserved1 = 0;
  unsigned short h_reserved2 = 0;
  unsigned h_off_bits = header_size + info_size;

  std::ofstream out(file_name.c_str(), std::ios::binary);
  if (out.is_open()) {
    out.write(reinterpret_cast<const char*>(&h_type), sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&h_size), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&h_reserved1),
              sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&h_reserved2),
              sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&h_off_bits), sizeof(unsigned));

    out.write(reinterpret_cast<const char*>(&i_size), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_width), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_height), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_planes), sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&i_bit_count),
              sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&i_compression), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_size_image), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_xpm), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_ypm), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_clru), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_clri), sizeof(unsigned));

    for (unsigned i = 0; i < height_; ++i) {
      const unsigned char* data_ptr =
          byte_data.data() + ((width_ * 3) * (height_ - i - 1));
      out.write(reinterpret_cast<const char*>(data_ptr),
                sizeof(unsigned char) * 3 * width_);
      out.write(padding_data, padding);
    }
    out.close();
    return true;
  }
  return false;
}

bool specula::image::Image::WritePng(std::string file_name) {
  FILE* file = fopen(file_name.c_str(), "wb");
  if (!file) {
    return false;
  }
  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    return false;
  }
  png_infop info = png_create_info_struct(png);
  if (!info) {
    return false;
  }
  if (setjmp(png_jmpbuf(png))) {
    return false;
  }
  unsigned char** byte_data = (png_bytepp)malloc(height_ * sizeof(png_bytep));
  for (unsigned i = 0; i < height_; i++) {
    byte_data[i] = (png_bytep)malloc(6 * width_ * sizeof(png_byte));
  }
  for (unsigned x = 0; x < width_; ++x) {
    for (unsigned y = 0; y < height_; ++y) {
      unsigned id = 6 * x;
      unsigned pixel = (x + (y * width_)) * 3;
      unsigned r = (pixel_data_[pixel] * 65535 + 0.5);
      unsigned g = (pixel_data_[pixel + 1] * 65535 + 0.5);
      unsigned b = (pixel_data_[pixel + 2] * 65535 + 0.5);
      byte_data[y][id] =
          static_cast<char>(std::floor(static_cast<double>(r) / 256.0));
      byte_data[y][id + 1] = static_cast<char>(r % 256);
      byte_data[y][id + 2] =
          static_cast<char>(std::floor(static_cast<double>(g) / 256.0));
      byte_data[y][id + 3] = static_cast<char>(g % 256);
      byte_data[y][id + 4] =
          static_cast<char>(std::floor(static_cast<double>(b) / 256.0));
      byte_data[y][id + 5] = static_cast<char>(b % 256);
    }
  }
  png_init_io(png, file);
  png_set_IHDR(png, info, width_, height_, 16, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);
  png_write_image(png, byte_data);
  png_write_end(png, NULL);
  png_free_data(png, info, PNG_FREE_ALL, -1);
  png_destroy_write_struct(&png, (png_infopp)NULL);
  fclose(file);
  return true;
}

std::vector<float> specula::image::Image::Data() { return pixel_data_; }

std::vector<unsigned char> specula::image::Image::GetByteImg(ByteOrder order) {
  std::vector<unsigned char> byte_data(3 * size_);
  for (unsigned x = 0; x < width_; ++x) {
    for (unsigned y = 0; y < height_; ++y) {
      unsigned pixel = (x + (y * width_)) * 3;
      unsigned char r = 255 * pixel_data_[pixel + 0],
                    g = 255 * pixel_data_[pixel + 1],
                    b = 255 * pixel_data_[pixel + 2];
      switch (order) {
        case RGB:
          byte_data[pixel + 0] = r;
          byte_data[pixel + 1] = g;
          byte_data[pixel + 2] = b;
        case RBG:
          byte_data[pixel + 0] = r;
          byte_data[pixel + 1] = b;
          byte_data[pixel + 2] = g;
        case GBR:
          byte_data[pixel + 0] = g;
          byte_data[pixel + 1] = b;
          byte_data[pixel + 2] = r;
        case GRB:
          byte_data[pixel + 0] = g;
          byte_data[pixel + 1] = r;
          byte_data[pixel + 2] = b;
        case BRG:
          byte_data[pixel + 0] = b;
          byte_data[pixel + 1] = r;
          byte_data[pixel + 2] = g;
        case BGR:
          byte_data[pixel + 0] = b;
          byte_data[pixel + 1] = g;
          byte_data[pixel + 2] = r;
      }
    }
  }
  return byte_data;
}
