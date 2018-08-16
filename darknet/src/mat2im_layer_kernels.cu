#include "cuda_runtime.h"
#include "curand.h"
#include "cublas_v2.h"
#include "mat2im_layer.h"
extern "C" {
#include "cuda.h"
}


__global__ void mat2im_kernel(int index, unsigned char *in, int n, int w, int h, int c, unsigned char *out, float ratio, float *resizeout)
{
    int id = (blockIdx.x + blockIdx.y*gridDim.x) * blockDim.x + threadIdx.x;
    if (id >= n) return;
    int iid = id;
    int k = 2 - (id%c);
    id /= c;
    int j = id % w;
    id /= w;
    int i = id;
    int start = w * (index%4) + (index/4) * h * w * 4;
    int out_index = k*8*w*h + start + i*w*4 + j;
    //int in_index = (2-k)+c*j+c*w*i;
    out[out_index] = in[iid];

    i *= ratio;
    j *= ratio;
    w *= ratio;
    h *= ratio;
    start = w * (index%4) + (index/4) * h * w * 4;
    out_index = k*8*w*h + start + i*w*4 + j;
    resizeout[out_index] = in[iid] / 255.0;
}

void mat2im(int index, unsigned char *in, int n, int w, int h, int c, float *out, float ratio, float *resizeout)
{
    mat2im_kernel<<<cuda_gridsize(n), BLOCK>>>(index, in, n, w, h, c, (unsigned char*)out, ratio, resizeout);
    check_error(cudaPeekAtLastError());
}
