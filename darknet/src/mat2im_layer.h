#ifndef MAT2IM_LAYER_H
#define MAT2IM_LAYER_H

#include "opencv2/core.hpp"

struct mat2imLayer{
    size_t n;
    float ratio;
    float *out_gpu;
    float *resize_out_gpu;
    unsigned char *in_gpu;
};

struct mat2imLayer make_mat2im_layer(int w, int h, int c, float r);
void foward_mat2im_layer(struct mat2imLayer layer, cv::InputArray src, int index);
void fetch_out_gpu(struct mat2imLayer layer, float* dst, float* dst1);
void mat2im(int index, unsigned char *in, int n, int w, int h, int c, float *out, float ratio, float *resizeout);

#endif
