#include <iostream>

#include "specula.hpp"
#ifdef __OPEN_CL__
#include <CL/cl.hpp>
#endif

int main(int argc, char const* argv[]) {
#ifdef __OPEN_CL__
  // get all platforms (drivers)
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);
  if (all_platforms.size() == 0) {
    std::cout << " No platforms found. Check OpenCL installation!\n";
    exit(1);
  }
  cl::Platform default_platform = all_platforms[0];
  std::cout << "Using platform: "
            << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";
  // get default device of the default platform
  std::vector<cl::Device> all_devices;
  default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
  if (all_devices.size() == 0) {
    std::cout << " No devices found. Check OpenCL installation!\n";
    exit(1);
  }
  cl::Device default_device = all_devices[0];
  std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>()
            << "\n";
#endif

  specula::Scene scene;
  specula::Material mat;
  mat.diffuse = {1.0, 0.0, 1.0};
  scene.objects.push_back(specula::CreateObjectSphere(1.0, mat));
  scene.objects.back()->Translate(0.0, 0.0, 10.0);
  mat.diffuse = {0.0, 1.0, 1.0};
  mat.emisivity = 1.0;
  scene.objects.push_back(specula::CreateObjectSphere(0.25, mat));
  scene.objects.back()->Translate(3.0, 0.0, 10.0);
  specula::Image img = specula::RenderImage(100, 100, scene, {2, 100});
  std::cout << img.WriteAnsii();
  // img.WritePng("test.png");
  // specula::Color c = specula::CastRay({0, 0, 0}, {1, 0, 0}, scene, {0, 10});
  //
  // specula::Image img(80, 40);
  // img.Grad(1.0, 0.0, 1.0, 0.0, 1.0, 1.0);
  // img.SetPixel(25, 25, c.r, c.g, c.b);
  // std::cout << img.WriteAnsii();
  /* code */
  return 0;
}
