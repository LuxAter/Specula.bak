#include "specula/gpu.hpp"

#include <vector>

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "specula/dev.hpp"

static cl::Context global_context;

bool specula::gpu::initialize() {
  specula::logger::initialize_logger("OpenCL");
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);
  if (all_platforms.size() == 0) {
    LCERROR("OpenCL", "No platforms found. Check OpenCL installation");
    return false;
  }
  std::vector<cl::Device> compute_devices;
  for (auto& platform : all_platforms) {
    LCINFO("OpenCL", "Platform: {}[{}]", platform.getInfo<CL_PLATFORM_NAME>(),
           platform.getInfo<CL_PLATFORM_VERSION>());
    std::vector<cl::Device> all_devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0) {
      LCERROR("OpenCL", "  Platform has no devices");
    }
    for (auto& device : all_devices) {
      compute_devices.push_back(device);
      LCINFO("OpenCL", "  Device: {}[{}]", device.getInfo<CL_DEVICE_NAME>(),
             device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>());
    }
  }
  if (compute_devices.size() == 0) {
    LCERROR("OpenCL", "No devices found. Check OpenCL installation");
  }
  global_context = cl::Context(compute_devices);
  return true;
}

