#ifndef __FUCN_H__
#define __FUCN_H__

#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

namespace ImageHandle{
	//功能与python中numpy的argsort相同
	Mat argsort(InputArray _src, bool ascending=false);
}
#endif