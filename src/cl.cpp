#define NUM_THREADS 16
#include "specula/cl.hpp"

#include <iostream>
#include <vector>

#ifdef __HAS_OPENCL__
#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#endif

#include "specula/geometry/geometry.hpp"
#include "specula/log.hpp"
#include "specula/primatives/primatives.hpp"

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
}
#else
void specula::opencl::log_info() {
  lwarning("This binary has not been compiled with OpenCL");
}
#endif

#ifdef __HAS_OPENCL__
std::function<std::vector<specula::intersect>(std::vector<specula::ray>)>
specula::opencl::generate_function(
    std::vector<std::shared_ptr<specula::Primative>> objs) {
  std::vector<cl::Device> all_devices;
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);
  for (auto &it : platforms) {
    std::vector<cl::Device> devices;
    it.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    all_devices.insert(all_devices.end(), devices.begin(), devices.end());
  }
  cl::Context context(all_devices);

  std::string kernel_code = "";
  std::vector<std::string> functions;
  for (auto &it : objs) {
    kernel_code += it->gen_function() + "\n";
    functions.push_back("de" + it->id_);
  }
  kernel_code +=
      "void kernel distance_estimator(global const float3 *origins,\n"
      "                               global const float3 *dirs,\n"
      "                               const float size, global int "
      "*obj_index,\n"
      "                               global float *times, global float3 "
      "*normals) {\n"
      "  int ID = get_global_id(0);\n"
      "  int WORKERS = get_global_size(0);\n"
      "  int step = (size / WORKERS);\n"
      "  for (int i = ID * step; i < step * (ID + 1); ++i) {\n"
      "    int obj_ind = -1;\n"
      "    float t = 0;\n"
      "    while (t < 1e5f) {\n"
      "      float3 p = origins[i] + dirs[i] * t;\n"
      "      float dt = INFINITY;\n"
      "      float odt = INFINITY;\n";
  for (std::size_t i = 0; i < objs.size(); ++i) {
    kernel_code += fmt::format("odt = de_%s(p); if (odt < dt) { dt = odt; if "
                               "(odt < 1e-5f) { obj_ind = %lu; } }",
                               objs[i]->id_.c_str(), i);
  }
  // kernel_code +=
  //     " if (dt < 1e-5f) { break; } else { t += dt; } } obj_index[i] = -1; "
  //     "times[i] = t; if (obj_ind != -1) { normals[i] = (float3)(0.0f, 0.0f, "
  //     "0.0f); } else { normals[i] = (float3)(0.0f, 0.0f, 0.0f); } } }";
  kernel_code +=
      " if (dt < 1e-5f) { break; } else {t += dt; }} obj_index[i] = 0; times[i] = 0.0f; normals[i] = (float3)(0.0f, 0.0f, 0.0f); }}";
  kernel_code = "void kernel distance_estimator(global const float3 *origins, global const float3 *dirs, const float size, global int *obj_index, global float*times, global float3* normals){int ID = get_global_id(0); obj_index[ID]=0; times[ID]=0.0f;}";
  std::cout << kernel_code << "\n";
  cl::Program::Sources sources;
  sources.push_back({kernel_code.c_str(), kernel_code.length()});

  cl::Program program(context, sources);
  if (program.build(all_devices) != CL_SUCCESS) {
    lfatal("Failed to build OpenCL kernel");
    for (auto &it : all_devices) {
      lfatal("  CL BUILD LOG: %s",
             program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(it).c_str());
      std::cerr << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(it);
    }
  }
  cl::CommandQueue clqueue(context, all_devices[0]);
  std::shared_ptr<cl::Kernel> distance_estimator =
      std::make_shared<cl::Kernel>(program, "distance_estimator");
  return [clqueue, context,
          distance_estimator](std::vector<ray> rays) -> std::vector<intersect> {
    cl::Buffer buff_origins(context, CL_MEM_READ_WRITE,
                            sizeof(cl_float3) * rays.size());
    cl::Buffer buff_dirs(context, CL_MEM_READ_WRITE,
                         sizeof(cl_float3) * rays.size());
    cl::Buffer buff_obj_index(context, CL_MEM_READ_WRITE,
                              sizeof(cl_int) * rays.size());
    cl::Buffer buff_time(context, CL_MEM_READ_WRITE,
                         sizeof(cl_float) * rays.size());
    cl::Buffer buff_normals(context, CL_MEM_READ_WRITE,
                            sizeof(cl_float3) * rays.size());

    std::vector<cl_float3> cl_origins, cl_dirs;
    for (auto &it : rays) {
      cl_origins.push_back({{it.o.x, it.o.y, it.o.z}});
      cl_dirs.push_back({{it.d.x, it.d.y, it.d.z}});
    }
    clqueue.enqueueWriteBuffer(buff_origins, CL_TRUE, 0,
                               sizeof(cl_float3) * rays.size(),
                               cl_origins.data());
    clqueue.enqueueWriteBuffer(buff_dirs, CL_TRUE, 0,
                               sizeof(cl_float3) * rays.size(), cl_dirs.data());

    distance_estimator->setArg(0, buff_origins);
    distance_estimator->setArg(1, buff_dirs);
    distance_estimator->setArg(2, rays.size());
    distance_estimator->setArg(3, buff_obj_index);
    distance_estimator->setArg(4, buff_time);
    distance_estimator->setArg(5, buff_normals);
    clqueue.enqueueNDRangeKernel(*distance_estimator, cl::NullRange,
                                 cl::NDRange(1), cl::NullRange);
    clqueue.finish();
    int *cl_obj_ind = (int *)malloc(sizeof(int) * rays.size());
    float *cl_times = (float *)malloc(sizeof(float) * rays.size());
    cl_float3 *cl_normals =
        (cl_float3 *)malloc(sizeof(cl_float3) * rays.size());
    clqueue.enqueueReadBuffer(buff_obj_index, CL_TRUE, 0,
                              sizeof(cl_int) * rays.size(), cl_obj_ind);
    clqueue.enqueueReadBuffer(buff_time, CL_TRUE, 0,
                              sizeof(cl_float) * rays.size(), cl_times);
    clqueue.enqueueReadBuffer(buff_normals, CL_TRUE, 0,
                              sizeof(cl_float3) * rays.size(), cl_normals);
    std::vector<intersect> intersections;
    for (std::size_t i = 0; i < rays.size(); ++i) {
      intersections.push_back(
          {cl_obj_ind[i],
           cl_times[i],
           {cl_normals[i].s[0], cl_normals[i].s[1], cl_normals[i].s[2]}});
      // ldebug("%i: %i, %f", i, cl_obj_ind[i], cl_times[i]);
    }
    return intersections;
  };
}
#else
std::function<std::vector<specula::intersect>(std::vector<specula::ray>)>
specula::opencl::generate_function(
    std::vector<std::shared_ptr<specula::Primative>> objs) {
  float T_MAX = 1e5;
  float EPSILON = 1e-5;
  return
      [objs, T_MAX, EPSILON](std::vector<ray> rays) -> std::vector<intersect> {
        std::vector<intersect> intersects;
        for (auto &ray : rays) {
          int obj_index = -1;
          float t = 0;
          while (t < T_MAX) {
            glm::vec3 p = ray(t);
            float dt = std::numeric_limits<float>::infinity();
            for (std::size_t i = 0; i < objs.size(); ++i) {
              float odt = objs[i]->distance(p);
              if (odt < dt) {
                dt = odt;
                if (odt < EPSILON) {
                  obj_index = i;
                }
              }
            }
            if (dt < EPSILON)
              break;
            else
              t += dt;
          }
          if (obj_index != -1) {
            intersects.push_back({obj_index, t, {0.0f, 0.0f, 0.0f}});
          } else {
            intersects.push_back({-1, 5, {0.0f, 0.0f, 0.0f}});
          }
        }
        return intersects;
      };
}
#endif
