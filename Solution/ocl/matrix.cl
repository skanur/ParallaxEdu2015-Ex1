__kernel void simpleAdd(
         __global float* outputC,
        __global float* inputA,
        __global float* inputB)
        {
int i = get_global_id(0);
outputC[i] = inputA[i] + inputB[i];
}