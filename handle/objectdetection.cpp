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
		 blob = cv::dnn::blobFromImage(img, 0.007843, Size(300, 300));
		 net.setInput(blob);

		 long start = GetMills();
		 detections = net.forward();
		 cout<<"rows:"<<detections.rows<<
		 	" cols:"<<detections.cols<<
		 	" dims:"<<detections.dims<<
		 	" channles:"<<detections.channels()<<
		 	" data:"<< detections.data<<endl;
		 int h =  detections.rows, w = detections.cols;

		 long end = GetMills();
		 long used = end - start;
		 cout<< GetTimestamp()<<" "<<
		 	"ObjectDetectionDL handle a image, computing object detections took "<< used <<" ms"<< endl;
		 //创建等差数组,类似于python的np.arange
		 int channels = detections.channels();
		 vector<int> inds;
		 for (int i=0; i< channels; i++){
		 	inds.push_back(i);
		 }
		 //拼装返回数据
		 stringstream desc;
		 float confidence = 0.2; //minimum probability to filter weak detections

		 /*
		 for(int i=0; i< inds.size(); i++){
		 	// extract the confidence (i.e., probability) associated with the
			// prediction

		 	int ind = inds[i];
		 	string label = labels[ind];
		 	float probability = preds.at<float>(ind);
		 	char buff[100];
		 	sprintf(buff, "%.4f", probability);
		 	if (i == 0){
		 		stringstream text; 
				text<<"Lable:"<<label<<","<< string(buff);	
				cv::putText(img, text.str(), Point(5, 25),
					cv::FONT_HERSHEY_SIMPLEX, 0.7,
					Scalar(0,0,255), 2);
		 	}
		 	desc<< i+1<< " label: "<< label << 
		 		", probalitiy: "<< string(buff)<<endl;

		 }
		 _return.desc = desc.str();
		 vector<uchar> buf;
		bool status = cv::imencode(".jpg", img, buf);
		if (status){
			_return.ret = string(buf.begin(), buf.end());
		}else{
			cout<< GetTimestamp()<<" "<<
				 "ObjectDetectionDL cv::imencode fail."<<endl;
		}
		*/
	}
	//这里初始化单实例
	ObjectDetectionDL* ObjectDetectionDL::instance = new ObjectDetectionDL();
	ObjectDetectionDL* ObjectDetectionDL::getInstance(){
		return instance;
	}
}