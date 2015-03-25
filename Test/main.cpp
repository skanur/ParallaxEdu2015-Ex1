#if __cplusplus <= 199711L
    #error This project can only be compiled with a compiler that supports C++11
#endif

#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

#include <iostream>
#include <vector>
#include <string>

int main (int argc, char *argv[]){
  VECTOR_CLASS<cl::Platform> allPlatforms;
  cl::Platform::get(&allPlatforms);

  if(allPlatforms.empty()) {
    std::cerr << "No Platforms found" << std::endl;
  } else {
    std::cout << "Platforms available: " << std::endl;
    for(const auto& p : allPlatforms) {
      std::cout << p.getInfo<CL_PLATFORM_NAME>() << std::endl;
      VECTOR_CLASS<cl::Device> allDevices;
      p.getDevices(CL_DEVICE_TYPE_ALL, &allDevices);
      if(allDevices.empty()){
	std::cerr << "No Devices found" << std::endl;
      }else {
	std::cout << "\tDevices on this platform: " << std::endl;
	for(const auto & d : allDevices) {
	  std::cout << "\t" << d.getInfo<CL_DEVICE_NAME>() << std::endl;
	  std::cout << std::endl;
	}
      }
      std::cout << std::endl;
    }
  }
  
  return 0;
}
        
    
