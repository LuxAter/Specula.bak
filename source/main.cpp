#include "specula.hpp"

int main(int argc, char *argv[])
{
  specula::image::Image img(4000, 1.0);
  img.Fill(0xfff00f);
  img.WritePng("test.png");
  return 0;
}
