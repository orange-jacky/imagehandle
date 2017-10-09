#include "objectdetection.h"

namespace ImageHandle{
	int ObjectDetectionDL::Init(){
		//读取配置
		Configure* conf = Configure::getInstance();		
		prototxt_file = conf->c.od_prototxt;
		model_file = conf->c.od_mode;
		label_file = conf->c.od_labels;
		//载入模型
		net = cv::dnn::readNetFromCaffe(prototxt_file, model_file);
		//载入labels
		string str[] = {"background", "aeroplane", "bicycle", "bird", "boat",
						"bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
						"dog", "horse", "motorbike", "person", "pottedplant", "sheep",
						"sofa", "train", "tvmonitor"};
		int num = sizeof(str)/sizeof(string);
		vector<string> CLASSES (str, str + num);
		labels.insert(labels.end(), CLASSES.begin(), CLASSES.end());

		return 0;
	}
	string  ObjectDetectionDL::String(){
			stringstream str;
			str<<"{prototxt:"<<prototxt_file<<",model:"<<model_file<<",label:"<< label_file<<
			 ",num of labels:"<<labels.size()<<"} ";
			return str.str();
	}
	void ObjectDetectionDL::handle(Result& _return, const string& image){
		 std::vector<char> vec_data(&image[0], &image[0]+ image.size());
		 Mat img, blob, detections;
		 img = imdecode(Mat(vec_data), 1);
		 int h =  img.rows, w = img.cols;

		 blob = cv::dnn::blobFromImage(img, 0.007843f, Size(300, 300), 127.5 );
		 net.setInput(blob);

		 long start = GetMills();
		 detections = net.forward();
		 //cout<< detections.size<<endl;
		 //这一步c++很重要, python不需要这一步
         Mat detectionMat(detections.size[2], detections.size[3], CV_32F, detections.ptr<float>());
		 //cout<< detectionMat<<endl;

		 long end = GetMills();
		 long used = end - start;
		 cout<< GetTimestamp()<<" "<<
		 	"ObjectDetectionDL handle a image, computing object detections took "<< used <<" ms"<< endl;
		
		 //拼装返回数据
		 string desc;
		 float confidenceThreshold = 0.2; //minimum probability to filter weak detections
		 
		 for(int i=0; i< detectionMat.rows; i++){
		 	// extract the confidence (i.e., probability) associated with the
			// prediction
		 	float confidence = detectionMat.at<float>(i, 2);
		 	if(confidence > confidenceThreshold){
		 		size_t objectClass = (size_t)(detectionMat.at<float>(i, 1));
		 		
		 		int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * w);
                int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * h);
                int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * w);
                int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * h);

                Rect object( (int)xLeftBottom, (int)yLeftBottom,
                             (int)(xRightTop - xLeftBottom),
                             (int)(yRightTop - yLeftBottom) );

                rectangle(img, object, Scalar(0, 255, 0) );
                stringstream ss;
                ss << confidence;
                string conf(ss.str());
               	string label = string(labels[objectClass]) + ":" + conf;

               	int baseLine = 0;
               	Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine );
               	rectangle(img, 
               			  Rect(Point(xLeftBottom, yLeftBottom - labelSize.height),
                               Size(labelSize.width, labelSize.height + baseLine) ),
                          Scalar(255, 255, 255), CV_FILLED);
               	putText(img, label, Point(xLeftBottom, yLeftBottom),
                        FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
               	//
               	desc += label + "\n";
		 	}
		 }
		 _return.desc = desc;
		vector<uchar> buf;
		bool status = cv::imencode(".jpg", img, buf);
		if (status){
			_return.ret = string(buf.begin(), buf.end());
		}else{
			cout<< GetTimestamp()<<" "<<
				 "ObjectDetectionDL cv::imencode fail."<<endl;
		}
	}
	//这里初始化单实例
	ObjectDetectionDL* ObjectDetectionDL::instance = new ObjectDetectionDL();
	ObjectDetectionDL* ObjectDetectionDL::getInstance(){
		return instance;
	}
}