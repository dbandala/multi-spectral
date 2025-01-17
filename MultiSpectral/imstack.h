// Daniel Bandala @ dec-2022
#pragma once
#include <filesystem>
#include <iostream>
#include <set>
#include <numeric>
#include <algorithm>
// kernel
#include "kernel.h"
// opencv lib
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
// cuda api lib
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudafilters.hpp>

struct HSVstack {
	std::vector<cv::cuda::GpuMat> h;
	std::vector<cv::cuda::GpuMat> s;
	std::vector<cv::cuda::GpuMat> v;
};

struct Vstack {
	std::vector<cv::Mat> v;
};

struct Statslabel {
	std::vector<int> left;
	std::vector<int> top;
	std::vector<int> width;
	std::vector<int> height;
};

struct Rectangle {
	int left;
	int top;
	int width;
	int height;
};

#define NUM_SPECT 100
struct Pixelarray {
	std::vector<std::array<float, NUM_SPECT>> val_h;
	std::vector<std::array<float, NUM_SPECT>> val_s;
	std::vector<std::array<float, NUM_SPECT>> val_v;
};

struct PixelarrayV {
	std::vector<std::array<float, NUM_SPECT>> val_v;
};

class imstack
{
	public:
		cv::Mat colorimg;
		cv::Mat colorimg32;
		std::vector<std::filesystem::path> sort_filename;
		Statslabel statslabel;
		cv::Mat final_label;
		HSVstack images;
		Vstack imagesv;
		Pixelarray Uobjpixels;
		PixelarrayV UobjpixelsV;
		std::vector<Pixelarray> colpixuniq;
		std::vector<cv::Mat> labelimag;

		imstack();
		~imstack();

		void colorread(std::string path, float scalef);
		void getfiles(std::string path);
		void createmask(int initialid, int numsamples, float scalef, float limit_v, int gx, int gy);
		void readstack(float scalef);
		void objpixels(Rectangle rectangle, int labelid, float limsimi);

		void readstackv(float scalef);
		void objpixelsv(Rectangle rectangle, int labelid, float limsimi, std::string multidirout);
};