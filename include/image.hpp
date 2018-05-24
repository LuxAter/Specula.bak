#ifndef SPECULA_IMAGE_HPP_
#define SPECULA_IMAGE_HPP_

#include <vector>
#include <string>

namespace specula {
namespace image {
  class Image {
   public:
     enum ByteOrder{
       RGB,
       RBG,
       GBR,
       GRB,
       BRG,
       BGR
     };
    Image();
    Image(unsigned px_w, unsigned px_h);
    ~Image();

    void SetPixel(unsigned x, unsigned y, int red, int green, int blue);
    void SetPixel(unsigned x, unsigned y, float red, float green, float blue);
    void SetPixel(unsigned x, unsigned y, double red, double green, double blue);

    void Fill(int red, int green, int blue);
    void Fill(float red, float green, float blue);
    void Fill(double red, double green, double blue);

    void Grad(double r1, double g1, double b1, double r2, double g2, double b2);

    bool WriteBitmap(std::string file);
    bool WritePng(std::string file);

    std::vector<float> Data();

   private:

    std::vector<unsigned char> GetByteImg(ByteOrder order=RGB);
    unsigned width_, height_, size_;
    std::vector<float> pixel_data_;
  };
}  // namespace image
}  // namespace specula

#endif  // SPECULA_IMAGE_HPP_
