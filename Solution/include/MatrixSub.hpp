#pragma once

#include <CL/cl.hpp>
#include <vector>
#include <map>
#include <cerrno>
#include <cstdlib>

// For reading UTF-8 files
#include <fstream>
#include <iostream>
#include <string>

#include "OclObject.hpp"
#include "../ocl/matrix.cl"

class MatrixSub : public MatrixAdd {
public:
  MatrixSub(const OclObject &ocl);
  void compute();
  bool verify();
};

MatrixSub::MatrixSub(const OclObject &ocl) : MatrixAdd::MatrixAdd(ocl) {  
  try{
    VECTOR_CLASS<cl::Device> usedDeviceVector;
    usedDeviceVector.push_back(_usedDevice);
    _matrix = cl::Kernel(_program, "simpleSub");
    _matrix.setArg(0, _bufferC);
    _matrix.setArg(1, _bufferA);
    _matrix.setArg(2, _bufferB);

    _queue.enqueueWriteBuffer(_bufferA, CL_TRUE, 0, _width * sizeof(float), _A);
    _queue.enqueueWriteBuffer(_bufferB, CL_TRUE, 0, _width * sizeof(float), _B);
  } catch(cl::Error &err) {

    switch(err.err()) {
    case CL_BUILD_PROGRAM_FAILURE: {
      std::cerr << "Build Error: " << std::endl;
      cl::STRING_CLASS buildlog;
      _program.getBuildInfo(_usedDevice, CL_PROGRAM_BUILD_LOG, &buildlog);
      std::cerr << buildlog << std::endl;
      break;
    }
    default: {
      std::cerr << "Error: " << err.what() << "(" << err_code(err.err()) << ")" << std::endl;
      break;
    }
    }
  }
}

void MatrixSub::compute(){
  _queue.enqueueNDRangeKernel(_matrix, cl::NullRange, cl::NDRange(_width), cl::NullRange);
  std::cout << "Computed MatrixSub" << std::endl;
}

bool MatrixSub::verify(){
  try {
    _queue.enqueueReadBuffer(_bufferC, CL_TRUE, 0,_width * sizeof(float), _C);
  } catch(cl::Error &err) {
    std::cerr << "Error: " << err.what() << "(" << err_code(err.err()) << ")" << std::endl;
  }
  bool verified = false;
  for(int i = 0; i < _width ; i++) {
    verified |= (_C[i] == (_A[i] - _B[i]));
  }
  return verified;
}
