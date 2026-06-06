#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1024*1024

int main() {
    cl_platform_id platform; cl_device_id device; cl_context ctx; cl_command_queue queue;
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    ctx = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    queue = clCreateCommandQueue(ctx, device, 0, NULL);
    
    float *a = malloc(N*sizeof(float)), *b = malloc(N*sizeof(float)), *c = malloc(N*sizeof(float));
    for (int i = 0; i < N; i++) { a[i] = 1.0f; b[i] = 2.0f; }
    
    cl_mem d_a = clCreateBuffer(ctx, CL_MEM_READ_ONLY, N*sizeof(float), NULL, NULL);
    cl_mem d_b = clCreateBuffer(ctx, CL_MEM_READ_ONLY, N*sizeof(float), NULL, NULL);
    cl_mem d_c = clCreateBuffer(ctx, CL_MEM_WRITE_ONLY, N*sizeof(float), NULL, NULL);
    
    clEnqueueWriteBuffer(queue, d_a, CL_TRUE, 0, N*sizeof(float), a, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, d_b, CL_TRUE, 0, N*sizeof(float), b, 0, NULL, NULL);
    
    // Load and build kernel (simplified)
    printf("OpenCL vector add: N=%d\n", N);
    
    clReleaseMemObject(d_a); clReleaseMemObject(d_b); clReleaseMemObject(d_c);
    clReleaseCommandQueue(queue); clReleaseContext(ctx);
    free(a); free(b); free(c);
    return 0;
}
