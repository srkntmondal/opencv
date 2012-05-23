#include "perf_cpu_precomp.hpp"

#ifdef HAVE_CUDA

IMPLEMENT_PARAM_CLASS(KernelSize, int)

//////////////////////////////////////////////////////////////////////
// Blur

GPU_PERF_TEST(Blur, cv::gpu::DeviceInfo, cv::Size, MatType, KernelSize)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);
    int ksize = GET_PARAM(3);

    cv::Mat src(size, type);

    declare.in(src, WARMUP_RNG);

    cv::Mat dst;

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::blur(src, dst, cv::Size(ksize, ksize));
    }
}

INSTANTIATE_TEST_CASE_P(Filter, Blur, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4)),
    testing::Values(KernelSize(3), KernelSize(5), KernelSize(7))));

//////////////////////////////////////////////////////////////////////
// Sobel

GPU_PERF_TEST(Sobel, cv::gpu::DeviceInfo, cv::Size, MatType, KernelSize)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);
    int ksize = GET_PARAM(3);

    cv::Mat src(size, type);

    declare.in(src, WARMUP_RNG);

    cv::Mat dst;

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::Sobel(src, dst, -1, 1, 1, ksize);
    }
}

INSTANTIATE_TEST_CASE_P(Filter, Sobel, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4), MatType(CV_32FC1)),
    testing::Values(KernelSize(3), KernelSize(5), KernelSize(7), KernelSize(9), KernelSize(11), KernelSize(13), KernelSize(15))));

//////////////////////////////////////////////////////////////////////
// Scharr

GPU_PERF_TEST(Scharr, cv::gpu::DeviceInfo, cv::Size, MatType)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);

    cv::Mat src(size, type);

    declare.in(src, WARMUP_RNG);

    cv::Mat dst;

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::Scharr(src, dst, -1, 1, 0);
    }
}

INSTANTIATE_TEST_CASE_P(Filter, Scharr, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4), MatType(CV_32FC1))));

//////////////////////////////////////////////////////////////////////
// GaussianBlur

GPU_PERF_TEST(GaussianBlur, cv::gpu::DeviceInfo, cv::Size, MatType, KernelSize)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);
    int ksize = GET_PARAM(3);

    cv::Mat src(size, type);

    declare.in(src, WARMUP_RNG);

    cv::Mat dst;

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::GaussianBlur(src, dst, cv::Size(ksize, ksize), 0.5);
    }
}

INSTANTIATE_TEST_CASE_P(Filter, GaussianBlur, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4), MatType(CV_32FC1)),
    testing::Values(KernelSize(3), KernelSize(5), KernelSize(7), KernelSize(9), KernelSize(11), KernelSize(13), KernelSize(15))));

//////////////////////////////////////////////////////////////////////
// Laplacian

GPU_PERF_TEST(Laplacian, cv::gpu::DeviceInfo, cv::Size, MatType, KernelSize)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);
    int ksize = GET_PARAM(3);

    cv::Mat src(size, type);

    declare.in(src, WARMUP_RNG);

    cv::Mat dst;

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::Laplacian(src, dst, -1, ksize);
    }
}

INSTANTIATE_TEST_CASE_P(Filter, Laplacian, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4), MatType(CV_32FC1), MatType(CV_32FC4)),
    testing::Values(KernelSize(1), KernelSize(3))));

//////////////////////////////////////////////////////////////////////
// Erode

GPU_PERF_TEST(Erode, cv::gpu::DeviceInfo, cv::Size, MatType)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);

    cv::Mat src(size, type);

    declare.in(src, WARMUP_RNG);

    cv::Mat ker = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    cv::Mat dst;

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::erode(src, dst, ker);
    }
}

INSTANTIATE_TEST_CASE_P(Filter, Erode, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4))));

//////////////////////////////////////////////////////////////////////
// Dilate

GPU_PERF_TEST(Dilate, cv::gpu::DeviceInfo, cv::Size, MatType)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);

    cv::Mat src(size, type);

    declare.in(src, WARMUP_RNG);

    cv::Mat ker = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    cv::Mat dst;

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::dilate(src, dst, ker);
    }
}

INSTANTIATE_TEST_CASE_P(Filter, Dilate, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4))));

//////////////////////////////////////////////////////////////////////
// MorphologyEx

CV_ENUM(MorphOp, cv::MORPH_OPEN, cv::MORPH_CLOSE, cv::MORPH_GRADIENT, cv::MORPH_TOPHAT, cv::MORPH_BLACKHAT)
#define ALL_MORPH_OPS testing::Values(MorphOp(cv::MORPH_OPEN), MorphOp(cv::MORPH_CLOSE), MorphOp(cv::MORPH_GRADIENT), MorphOp(cv::MORPH_TOPHAT), MorphOp(cv::MORPH_BLACKHAT))

GPU_PERF_TEST(MorphologyEx, cv::gpu::DeviceInfo, cv::Size, MatType, MorphOp)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);
    int morphOp = GET_PARAM(3);

    cv::Mat src(size, type);

    declare.in(src, WARMUP_RNG);

    cv::Mat dst;

    cv::Mat ker = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::morphologyEx(src, dst, morphOp, ker);
    }
}

INSTANTIATE_TEST_CASE_P(Filter, MorphologyEx, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4)),
    ALL_MORPH_OPS));

//////////////////////////////////////////////////////////////////////
// Filter2D

GPU_PERF_TEST(Filter2D, cv::gpu::DeviceInfo, cv::Size, MatType, KernelSize)
{
    cv::Size size = GET_PARAM(1);
    int type = GET_PARAM(2);
    int ksize = GET_PARAM(3);

    cv::Mat src(size, type);
    cv::Mat kernel(ksize, ksize, CV_32FC1);

    declare.in(src, kernel, WARMUP_RNG);

    cv::Mat dst;

    declare.time(20.0);

    TEST_CYCLE()
    {
        cv::filter2D(src, dst, -1, kernel);
    }
}

INSTANTIATE_TEST_CASE_P(Filter, Filter2D, testing::Combine(
    ALL_DEVICES,
    GPU_TYPICAL_MAT_SIZES,
    testing::Values(MatType(CV_8UC1), MatType(CV_8UC4), MatType(CV_32FC1), MatType(CV_32FC4)),
    testing::Values(KernelSize(3), KernelSize(5), KernelSize(7), KernelSize(9), KernelSize(11), KernelSize(13), KernelSize(15))));

#endif