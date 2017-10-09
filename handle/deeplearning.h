#ifndef DEEPLEARNING_H
#define DEEPLEARNING_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/dnn/dnn.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

#include "../thrift/gen-cpp/ImageHandle_types.h"
#include "../util/configure.h"
#include "../util/util_string.h"
#include "../util/util_time.h"
#include "func.h"


using namespace cv;
using namespace std;
using namespace ::ImageHandle::util;

namespace ImageHandle{
	class DeepLearning {
	public:
		string prototxt_file;//配置文件
		string model_file;
		string label_file;
	private:
		static DeepLearning* instance;
		cv::dnn::Net net;
		vector<string> labels;
	public:
		int Init();
		string String();
		void handle(Result& _return, const string& image);
		//单实例
		static DeepLearning* getInstance();
	private:
		DeepLearning(){};
		~DeepLearning(){};
		//把复制构造函数和=操作符也设为私有,防止被复制
		DeepLearning(const DeepLearning&){};
		DeepLearning& operator=(const DeepLearning&){};
	};
}// namespace

#endif