#include "opencl_utils.hpp"

opencl_utils::opencl_utils(/* args */)
{
}

opencl_utils::~opencl_utils()
{
}

cl::Context opencl_utils::setup_device(int platform_num, int device_num)
{

  std::vector<cl::Platform> platforms;

  cl::Platform::get(&platforms);

  // In my case it's 1, yours might be 0
  this->platform = platforms[platform_num];

  std::vector<cl::Device> devices;
  platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);

  this->device = devices[device_num];
  auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
  auto version = device.getInfo<CL_DEVICE_VERSION>();
  auto name = device.getInfo<CL_DEVICE_NAME>();

  std::cout << vendor << std::endl;
  std::cout << version << std::endl;
  std::cout << name << std::endl;

  cl::Context context(device);
  this->context = context;
  return this->context;
}

cl::Program opencl_utils::load_program(std::string file_name){

  std::ifstream input_file(file_name);
    std::string file_content((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    
    cl::Program program(this->context,file_content);

    auto err = 0;
    try {
      err = program.build(std::vector<cl::Device>{this->device},"-cl-std=CL2.0");
      

    }catch(cl::BuildError const &e) {
        
        std::string log;
        auto cl_log = e.getBuildLog();
        for(size_t i=0;i<cl_log.size();i++) {
            log += "For device: ";
            log += cl_log[i].first.getInfo<CL_DEVICE_NAME>();
            log += "\n";
            log += cl_log[i].second;
        }
        std::cout << "Failed to build program source , log:\n" + log << std::endl;
        std::cout << e.what() << std::endl;

        
    }

  return program;

}