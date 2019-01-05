#ifndef SPECULA_THREAD_CL_HPP_
#define SPECULA_THREAD_CL_HPP_

#include <vector>

#if __OPEN_CL__
#ifdef __APPLE__
#include <OpenCL/opencl.hpp>
#else
#include <CL/cl.hpp>
#endif
#endif

namespace specula {
  namespace thread {
    extern cl::Platform default_platform_;

    void Init();
  } // namespace thread
} // namespace specula

#endif  // SPECULA_THREAD_CL_HPP_
