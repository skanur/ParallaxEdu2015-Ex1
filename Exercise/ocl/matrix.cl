#pragma once

#include <string>

const std::string matrixCL = \
"__kernel void simpleAdd("
"         __global float* outputC,"
"        __global float* inputA,"
"        __global float* inputB)"
"        {"
"int i = get_global_id(0);"
"outputC[i] = inputA[i] + inputB[i];"
"}"
""
"__kernel void simpleSub("
"         __global float* outputC,"
"        __global float* inputA,"
"        __global float* inputB)"
"        {"
"int i = get_global_id(0);"
"outputC[i] = inputA[i] - inputB[i];"
"}"
"";