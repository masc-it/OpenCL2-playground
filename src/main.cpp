
#include "opencl_include.h"
#include <iostream>
#include <fstream>
#include <iostream> 
#include <string>
#include <vector>

#include "opencl_utils.hpp"

void test1(opencl_utils & opencl_utils);
void arraystest(opencl_utils & opencl_utils);

int main() {

    auto ocl_utils = opencl_utils();

    auto context = ocl_utils.setup_device(1, 0);
    
    arraystest(ocl_utils);
    

    cl::finish();
    return 0;
}


void test1(opencl_utils & opencl_utils){
    auto program = opencl_utils.load_program("../kernels/test.cl");

    char buf[4];

    auto err = 0;
    cl::Buffer mem(opencl_utils.get_context(), CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buf));

    // the second param is the actual method's name (I called it hello_world)
    cl::Kernel kernel(program, "hello_world", &err);

    kernel.setArg(0, mem);


    cl::CommandQueue queue(opencl_utils.get_context(), opencl_utils.get_device());

    queue.enqueueTask(kernel);

    queue.enqueueReadBuffer(mem, CL_TRUE, 0, sizeof(buf), buf);

    std::cout << buf << std::endl;
}
void arraystest(opencl_utils & opencl_utils){

    auto program = opencl_utils.load_program("../kernels/arrays.cl");

    std::vector<int> vector(3);

    vector[0] = 1;
    vector[1] = 2;
    vector[2] = 3;

    std::vector<int> out_vector(3);

    auto size = sizeof(int) * vector.size();
    cl::Buffer mem(opencl_utils.get_context(), CL_MEM_READ_ONLY, size);
    cl::Buffer out_mem(opencl_utils.get_context(), CL_MEM_WRITE_ONLY , size);

    cl::Kernel kernel(program, "process_array");

    kernel.setArg(0, mem);
    kernel.setArg(1, out_mem);

    cl::CommandQueue queue(opencl_utils.get_context(), opencl_utils.get_device());

    // populate in buffer
    queue.enqueueWriteBuffer(mem, CL_TRUE, 0, size, vector.data());

    // enqueue kernel
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(vector.size()), cl::NDRange(1));

    // move output to out_vector
    queue.enqueueReadBuffer(out_mem, CL_TRUE, 0, size , out_vector.data());

    queue.enqueueReadBuffer(mem, CL_TRUE, 0, size , vector.data());

    for (size_t i = 0; i < out_vector.size(); i++)
    {
            std::cout << out_vector[i] << std::endl;

    }

    for (size_t i = 0; i < vector.size(); i++)
    {
            std::cout << vector[i] << std::endl;

    }
    


}
