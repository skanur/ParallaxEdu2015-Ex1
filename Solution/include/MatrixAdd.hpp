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

class MatrixAdd {
public:
  cl::Platform _defaultPlatform;
  cl::Device _usedDevice;
  cl::Context _context;
  cl::Program _program;
  cl::Program::Sources _src;
  cl::CommandQueue _queue;
  cl::Buffer _bufferA, _bufferB, _bufferC;
  cl::Kernel _matrix;

  int _width;
  float *_A, *_B, *_C;
  
  MatrixAdd(const OclObject &ocl);
  ~MatrixAdd();

  //Copy constructor and its respective assignment
  MatrixAdd(const MatrixAdd&);
  MatrixAdd& operator=(const MatrixAdd&);

  //Move constructor and its respective assignment
  MatrixAdd(MatrixAdd&&);
  MatrixAdd& operator=(MatrixAdd&&);
  
  void compute();
  bool verify();
  int getWidth();
  
protected:  
  std::string getFileContents(const char *filename);
  std::pair <const char*, ::size_t> getKernelSource(const char *kernelFilename);
  
};

MatrixAdd::MatrixAdd(const OclObject &ocl) : _defaultPlatform(ocl.defaultPlatform), _usedDevice(ocl.usedDevice), _context(ocl.context), _queue(ocl.queue), _width(102400) {

  _A = new float[_width];
  _B = new float[_width];
  _C = new float[_width];
  
  for(int i = 0; i < _width ; i++) {
    _A[i] = rand() % RAND_MAX;
  }

  for(int i = 0; i < _width ; i++) {
    _B[i] = rand() % RAND_MAX;
  }
  
  try{
    VECTOR_CLASS<cl::Device> usedDeviceVector;
    usedDeviceVector.push_back(_usedDevice);
    _src.push_back(getKernelSource("../ocl/matrix.cl"));
    _program = cl::Program(_context, _src);
    _program.build(usedDeviceVector);
    _bufferA = cl::Buffer(_context, CL_MEM_READ_ONLY, _width * sizeof(float));
    _bufferB = cl::Buffer(_context, CL_MEM_READ_ONLY, _width * sizeof(float));
    _bufferC = cl::Buffer(_context, CL_MEM_WRITE_ONLY, _width * sizeof(float));
    _matrix = cl::Kernel(_program, "simpleAdd");
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

MatrixAdd::~MatrixAdd() {
  delete [] _A;
  delete [] _B;
  delete [] _C;
}

MatrixAdd::MatrixAdd(const MatrixAdd& m) {
  std::cout << "MatrixAdd:COPY" << std::endl;
  _width = m._width;
  _A = new float[_width];
  _B = new float[_width];
  _C = new float[_width];
  for(int i = 0; i < _width ; i++) {
    _A[i] = m._A[i];
    _B[i] = m._B[i];
    _C[i] = m._C[i];
  }
  _defaultPlatform = m._defaultPlatform;
  _usedDevice = m._usedDevice;
  _context = m._context;
  _program = m._program;
  _src = m._src;
  _queue = m._queue;
  _bufferA = m._bufferA;
  _bufferB = m._bufferB;
  _bufferC = m._bufferC;
  _matrix = m._matrix;
}

MatrixAdd& MatrixAdd::operator=(const MatrixAdd& m) {
  std::cout << "MatrixAdd:COPYAssignment" << std::endl;
  _width = m._width;
  for(int i = 0; i < _width ; i++) {
    _A[i] = m._A[i];
    _B[i] = m._B[i];
    _C[i] = m._C[i];
  }
  _defaultPlatform = m._defaultPlatform;
  _usedDevice = m._usedDevice;
  _context = m._context;
  _program = m._program;
  _src = m._src;
  _queue = m._queue;
  _bufferA = m._bufferA;
  _bufferB = m._bufferB;
  _bufferC = m._bufferC;
  _matrix = m._matrix;
  return *this;
}

MatrixAdd::MatrixAdd(MatrixAdd&& m) {
  std::cout << "MatrixAdd::MOVE" << std::endl;
  _width = m._width;
  _A = m._A;
  _B = m._B;
  _C = m._C;
  _defaultPlatform = std::move(m._defaultPlatform);
  _usedDevice = std::move(m._usedDevice);
  _context = std::move(m._context);
  _program = std::move(m._program);
  _src = std::move(m._src);
  _queue = std::move(m._queue);
  _bufferA = std::move(m._bufferA);
  _bufferB = std::move(m._bufferB);
  _bufferC = std::move(m._bufferC);
  _matrix = std::move(m._matrix);
  m._A = nullptr;
  m._B = nullptr;
  m._C = nullptr;
}

MatrixAdd& MatrixAdd::operator=(MatrixAdd&& m) {
  std::cout << "MatrixAdd::MOVEAssignment" << std::endl;
  _width = m._width;
  _A = m._A;
  _B = m._B;
  _C = m._C;
  _defaultPlatform = std::move(m._defaultPlatform);
  _usedDevice = std::move(m._usedDevice);
  _context = std::move(m._context);
  _program = std::move(m._program);
  _src = std::move(m._src);
  _queue = std::move(m._queue);
  _bufferA = std::move(m._bufferA);
  _bufferB = std::move(m._bufferB);
  _bufferC = std::move(m._bufferC);
  _matrix = std::move(m._matrix);
  m._A = nullptr;
  m._B = nullptr;
  m._C = nullptr;
  return *this;
}

void MatrixAdd::compute(){
  _queue.enqueueNDRangeKernel(_matrix, cl::NullRange, cl::NDRange(_width), cl::NullRange);
  std::cout << "Computed MatrixAdd" << std::endl;
}

bool MatrixAdd::verify(){
  try {
    _queue.enqueueReadBuffer(_bufferC, CL_TRUE, 0,_width * sizeof(float), _C);
  } catch(cl::Error &err) {
    std::cerr << "Error: " << err.what() << "(" << err_code(err.err()) << ")" << std::endl;
  }
  bool verified = false;
  for(int i = 0; i < _width ; i++) {
    verified |= (_C[i] == (_A[i] + _B[i]));
  }
  return verified;
}

int MatrixAdd::getWidth() {
  return _width;
}

std::string MatrixAdd::getFileContents(const char *filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if(in){
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

std::pair<const char*, ::size_t> MatrixAdd::getKernelSource(const char *kernelFilename) {
  std::ifstream in(kernelFilename, std::ios::in);
  if(in){
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    ::size_t kernelSize = in.tellg();
    in.seekg(0,std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(std::make_pair(contents.c_str(), kernelSize));
  }
  throw(errno);
}
