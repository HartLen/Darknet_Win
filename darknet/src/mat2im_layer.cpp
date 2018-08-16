

#include "cuda.h"

#include "opencv2/core.hpp"
#include "mat2im_layer.h"

using namespace cv;

struct mat2imLayer make_mat2im_layer(int w, int h, int c, float r)
{
    struct mat2imLayer layer;
    layer.ratio = r;
    layer.n = w*h*c;
    layer.in_gpu = NULL;
#ifdef GPU
    layer.out_gpu = cuda_make_array(NULL, layer.n / sizeof(float));
    layer.resize_out_gpu = cuda_make_array(NULL, layer.n*r*r);
#endif
    return layer;
}

void foward_mat2im_layer(struct mat2imLayer layer, InputArray _src, int index)
{
#ifdef GPU
    Mat src = _src.getMat();
    cudaMalloc((void **)&layer.in_gpu, src.cols*src.rows*src.step/src.cols);
    cudaMemcpy(layer.in_gpu, src.data, src.cols*src.rows*src.step/src.cols, cudaMemcpyHostToDevice);

    mat2im(index, layer.in_gpu, src.cols*src.rows*src.step/src.cols, src.cols, src.rows, src.step/src.cols, layer.out_gpu, layer.ratio, layer.resize_out_gpu);
    cudaFree(layer.in_gpu);
#endif
}

void fetch_out_gpu(struct mat2imLayer layer, float* dst, float* dst1)
{
#ifdef GPU
    cuda_pull_array(layer.out_gpu, dst, layer.n / sizeof(float));
    cuda_pull_array(layer.resize_out_gpu, dst1, layer.n*layer.ratio*layer.ratio);
#endif
}
