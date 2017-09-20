#ifndef COLORDESCRIPTOR_H
#define COLORDESCRIPTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

namespace ImageHandle {
	class ColorDescriptor{
	public:
		ColorDescriptor(){};
		~ColorDescriptor(){};
		int* histSize;
		void describe(const std::string& image, std::vector<double>& vect);
		void histogram(Mat &mat, InputArray &mask, std::vector<double>& vect);
	};
	bool isNan(double fN);
	bool isInf(double fN);
}// namespace

#endif
