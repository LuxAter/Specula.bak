#include <iostream>

#include "image.hpp"

int main(int argc, char const* argv[])
{
  specula::image::Image img(500, 500);
  img.Grad(1.0, 0.0, 0.5, 0.0, 0.5, 1.0);
  img.WriteBitmap("tmp.bmp");
  /* code */
  return 0;
}
