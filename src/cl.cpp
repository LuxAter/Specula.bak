#include "specula/cl.hpp"

#include <vector>

#ifdef __HAS_OPENCL__
#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#endif

#include "specula/log.hpp"

#ifdef __HAS_OPENCL__
void specula::opencl::log_info() {
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);
  for (auto &it : platforms) {
    linfo("CL Platform: %s", it.getInfo<CL_PLATFORM_NAME>().c_str());
    std::vector<cl::Device> devices;
    it.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    for (auto &dev : devices) {
      linfo("  CL Device: %s (%d)", dev.getInfo<CL_DEVICE_NAME>().c_str(),
            dev.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>());
    }
  }
  // cl_uint platform_count;
  // clGetPlatformIDs(0, NULL, &platform_count);
  // cl_platform_id *platforms = static_cast<cl_platform_id *>(
  //     std::malloc(sizeof(cl_platform_id) * platform_count));
  // clGetPlatformIDs(platform_count, platforms, NULL);
  // for (std::size_t i = 0; i < platform_count; ++i) {
  //   std::size_t info_size;
  //   clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 0, NULL, &info_size);
  //   char *info = static_cast<char *>(std::malloc(info_size));
  //   clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, info_size, info, NULL);
  //   linfo("Platform %lu: %s", i + 1, info);
  //   free(info);
  //   cl_uint device_count;
  //   clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &device_count);
  //   cl_device_id *devices = static_cast<cl_device_id *>(
  //       std::malloc(sizeof(cl_device_id) * device_count));
  //   clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, device_count, devices,
  //                  NULL);
  //   for (std::size_t j = 0; j < device_count; ++j) {
  //     std::size_t value_size;
  //     clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &value_size);
  //     char *value = static_cast<char *>(std::malloc(value_size));
  //     clGetDeviceInfo(devices[j], CL_DEVICE_NAME, value_size, value, NULL);
  //     cl_uint max_compute_units;
  //     clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS,
  //                     sizeof(max_compute_units), &max_compute_units, NULL);
  //     linfo("  Device %lu: %s (%d)", j + 1, value, max_compute_units);
  //     free(value);
  //   }
  // }
}
#else
void specula::opencl::log_info() {
  lwarning("This binary has not been compiled with OpenCL");
}
#endif
