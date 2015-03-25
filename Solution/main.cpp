#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "include/OclObject.hpp"
#include "include/MatrixAdd.hpp"

void copyExperiment() {
  OclObject poclOcl;

  MatrixAdd k1(poclOcl);
  k1.compute();
  
  MatrixAdd k2(k1);
  k2.compute();

  if(!k1.verify() || !k2.verify()) {
    std::cerr << "Copy Experiment - Verification Failed" << std::endl;
  }
}

void moveExperiment() {
  OclObject poclOcl;
  MatrixAdd k1(std::move(poclOcl));
  k1.compute();
  if(!k1.verify()) std::cerr << "Move Experiment k1 - Verification failed" << std::endl;

  MatrixAdd k2(std::move(k1));
  k2.compute();
  
  if(!k2.verify()) std::cerr << "Move Experiment k2 - Verification Failed" << std::endl;
 }


int main (int argc, char *argv[]){

  // Time copy experiment
  auto start = std::chrono::steady_clock::now();  
  copyExperiment();
  auto end = std::chrono::steady_clock::now();
  auto copyTime = std::chrono::duration<double> (end - start).count();
  std::cout << "Copy time - " << copyTime << std::endl;
  
  
  // Time move experiment
  start = std::chrono::steady_clock::now();
  moveExperiment();
  end = std::chrono::steady_clock::now();
  auto moveTime = std::chrono::duration<double> (end - start).count();
  std::cout << "Move time - " << moveTime << std::endl;
  
  return 0;
}
        
    
