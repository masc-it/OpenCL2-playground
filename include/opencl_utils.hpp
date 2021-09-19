#include "opencl_include.h"
#include <iostream>
#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
class opencl_utils
{
private:
  cl::Platform platform;
  cl::Device device;
  cl::Context context;

public:
  opencl_utils();
  ~opencl_utils();

  cl::Context setup_device(int platform_num, int device_num);
  cl::Program load_program(std::string);


  cl::Device get_device(){
    return device;
  }

  cl::Platform get_platform(){
    return platform;
  }

  cl::Context get_context(){
    return context;
  }


};




