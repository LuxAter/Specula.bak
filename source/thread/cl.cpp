#include "thread/cl.hpp"

#include <vector>
#include <iostream>

#if __OPEN_CL__
#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#endif

namespace specula::thread{
  cl::Platform default_platform_;
}

void specula::thread::Init(){
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);
  if(all_platforms.size() == 0){
    std::cerr << "No platforms found. Check OpenCL installation\n";
    return;
  }
  default_platform_ = all_platforms[0];
  for(auto& it : all_platforms){
    std::cout << "PLATFORM: " << it.getInfo<CL_PLATFORM_NAME>() << "\n";
  }
  std::vector<cl::Device> all_devices;
  default_platform_.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
  if(all_devices.size() == 0){
    std::cerr << "No devices found. Check OpenCL installation\n";
    return;
  }
  cl::Device default_device = all_devices[0];
  for(auto & it : all_devices){
    std::cout << "DEVICE: " << it.getInfo<CL_DEVICE_NAME>() << "\n";
  }
}
