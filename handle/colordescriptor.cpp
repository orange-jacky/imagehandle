#include "colordescriptor.h"

namespace ImageHandle {
	void ColorDescriptor::describe(const std::string& image, std::vector<double>& vect){
 		std::vector<char> vec_data(&image[0], &image[0]+ image.size());

 		Mat src, hsv;
 		src = imdecode(Mat(vec_data), 1);

 		// the features used to quantify the image
 		cvtColor(src, hsv, CV_BGR2HSV);

		// grab the dimensions and compute the center of the image
		int channels = hsv.channels();
		int h = hsv.rows, w = hsv.cols ;
 		int cX = int(w*0.5), cY = int(h*0.5); 

		// divide the image into four rectangles/segments (top-left,
		// top-right, bottom-right, bottom-left)
 		int segments[4][4] = { {0, cX, 0, cY}, {cX, w, 0, cY}, {cX, w, cY, h}, {0, cX, cY, h} };

 		//construct an elliptical mask representing the center of the
		//image
 		int axesX = int(w*0.75)/2, axesY = int(h*0.75)/2;

 		Mat ellipMask = Mat(h , w, CV_8UC1);
 		ellipse(ellipMask, Point(cX, cY), Size(axesX, axesY),0, 0, 360, Scalar(255), -1);
 		
 		// loop over the segments
 		for(int i=0; i<4; i++){
 			// construct a mask for each corner of the image, subtracting
			// the elliptical center from it
			int startX = segments[i][0], endX = segments[i][1], startY = segments[i][2], endY = segments[i][3];

			Mat cornerMask = Mat(h, w, CV_8UC1);
			rectangle(cornerMask, Point(startX, startY), Point(endX, endY), Scalar(255), -1);
			subtract(cornerMask, ellipMask, cornerMask);

			// extract a color histogram from the image, then update the
			// feature vector
			histogram(hsv, cornerMask, vect);
			//显示图形,左上,右上,右下,左下
			//std::stringstream  stream;
			//stream<< i;
			//imshow(stream.str(), cornerMask);
 		}
 		// extract a color histogram from the elliptical region and
		// update the feature vector
		histogram(hsv, ellipMask, vect);

		//显示椭圆 图形
		//imshow("ellipse", ellipMask);
		//imshow("source", src);
		//imshow("hsv:", hsv);
		//waitKey();
		std::cout<<"handle a image:<height,width,size>:"<<h<<","<<w<<","<<image.size()<<"byte"<<",number offeatures:"<<vect.size()<<std::endl;
	}

	void ColorDescriptor::histogram(Mat &image, InputArray mask, std::vector<double>& vect){

		int hbins = 8, sbins = 12, vbins = 3;
		int histSize[] = {hbins, sbins, vbins};  //h,s,v对应的值  h*s*v=288个double的数组

		float hranges[] = {0, 180}; //h 的范围
		float sranges[] = {0, 256}; //s 的范围
		float vranges[] = {0, 256}; //v 的范围
		const float* ranges[] = {hranges, sranges, vranges};
		int channels[] = {0, 1, 2};   //3个通道

		MatND hist;
		calcHist(&image, 1, channels, mask, hist, 3, histSize, ranges, true, false);
		//归一化处理
		normalize(hist, hist);

		//取特征值
		for(int h=0; h < hbins; h++){
			for(int s=0; s < sbins; s++){
				for(int v=0; v < vbins; v++){
					float binVal = hist.at<float>(h, s, v);
					if (isNan(binVal) || isInf(binVal)){
						vect.push_back(0);
					}else {
						vect.push_back(binVal);
					}
				}
			}
		}
	}  
	bool isNan(double x){
		return std::isnan(x);
	}
	bool isInf(double x){
		return std::isinf(x);
	}
} // namespace
