#pragma once

#include <CL/cl.hpp>
#include <vector>
#include <iostream>

#include "../include/err_code.h"

class OclObject {
public:
  OclObject();
  OclObject(cl::Platform &platform, cl::Device &device);
  cl::Platform defaultPlatform;
  cl::Device usedDevice;
  cl::Context context;
  cl::CommandQueue queue;

  //Copy constructors and respective assignment
  OclObject(const OclObject&);
  OclObject& operator=(const OclObject&);

  //Move constructor and respective assignment
  OclObject(OclObject&&);
  OclObject& operator=(OclObject&&);
  
private:
  void initializeRest();
};

OclObject::OclObject() {
  try {
    VECTOR_CLASS<cl::Platform> allPlatforms;
    VECTOR_CLASS<cl::Device> allDevices;

    cl::Platform::get(&allPlatforms);

    if(allPlatforms.size() == 0) {
      std::cerr << "No platforms found" << std::endl;
    } else {
      // Choose the first one in the list of platforms
      defaultPlatform = allPlatforms[0];
      std::cout << defaultPlatform.getInfo<CL_PLATFORM_NAME>() << std::endl;
    }

    defaultPlatform.getDevices(CL_DEVICE_TYPE_ALL, &allDevices);
    if(allDevices.size() == 0) {
      std::cerr << "No devices found" << std::endl;
    } else {
      usedDevice = allDevices[0];
    }
  } catch(cl::Error err) {
    std::cerr << "Error : " << err.what() << "(" << err_code(err.err()) << ")" << std::endl;
  }
  
  OclObject::initializeRest();
  
}

OclObject::OclObject(cl::Platform &platform, cl::Device &device) : defaultPlatform(platform), usedDevice(device) {
  OclObject::initializeRest();
}

void OclObject::initializeRest() {
  try {
    VECTOR_CLASS<cl::Device> usedDeviceVector;
    usedDeviceVector.push_back(usedDevice);
    context = cl::Context(usedDeviceVector);
    queue = cl::CommandQueue(context, usedDeviceVector[0]);
  } catch(cl::Error err) {
    std::cerr << "Error: " << err.what() << "(" << err_code(err.err()) << ")" << std::endl;
  }
}

OclObject::OclObject(const OclObject &o) {
  std::cout << "OClObject::COPY" << std::endl;
  defaultPlatform = o.defaultPlatform;
  usedDevice = o.usedDevice;
  context = o.context;
  queue = o.queue;
}

OclObject& OclObject::operator=(const OclObject &o) {
  std::cout << "OclObject::COPY Assignment" << std::endl;
  defaultPlatform = o.defaultPlatform;
  usedDevice = o.usedDevice;
  context = o.context;
  queue = o.queue;
  return *this;
}

OclObject::OclObject(OclObject&& o) {
  std::cout << "OclObject::MOVE" << std::endl;
  defaultPlatform = std::move(o.defaultPlatform);
  usedDevice = std::move(o.usedDevice);
  context = std::move(o.context);
  queue = std::move(o.queue);
}

OclObject& OclObject::operator=(OclObject&& o) {
  std::cout << "OclObject::MOVE Assignment" << std::endl;
  defaultPlatform = std::move(o.defaultPlatform);
  usedDevice = std::move(o.usedDevice);
  context = std::move(o.context);
  queue = std::move(o.queue);
  return *this;
}
