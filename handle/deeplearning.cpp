#include "deeplearning.h"

namespace ImageHandle{
	int DeepLearning::Init(){
		//读取配置
		Configure* conf = Configure::getInstance();		
		prototxt_file = conf->c.dp_prototxt;
		model_file = conf->c.dp_mode;
		label_file = conf->c.dp_labels;
		//载入模型
		net = cv::dnn::readNetFromCaffe(prototxt_file, model_file);
		//载入labels
		string line;
		ifstream myfile(label_file);
		if (myfile.is_open()){
			while(getline (myfile, line)){
				std::size_t pos = line.find(" ");
				std::string str = line.substr(pos+1);
				vector<string> v;
				splitStr(str , "," , v);
				if (v.size()> 0){
					labels.push_back(v[0]);
				}
			}
			myfile.close();
		}
		return 0;
	}
	string  DeepLearning::String(){
			stringstream str;
			str<<"{prototxt:"<<prototxt_file<<",model:"<<model_file<<",label:"<< label_file<<
			 ",num of labels:"<<labels.size()<<"} ";
			return str.str();
	}
	void DeepLearning::handle(Result& _return, const string& image){
		 std::vector<char> vec_data(&image[0], &image[0]+ image.size());
		 Mat img, blob, preds;
		 img = imdecode(Mat(vec_data), 1);
		 blob = cv::dnn::blobFromImage(img, 1, Size(244,244), Scalar(104, 117, 123));
		 net.setInput(blob);

		 long start = GetMills();
		 preds = net.forward();
		 long end = GetMills();
		 long used = end - start;
		 cout<< GetTimestamp()<<" "<<
		 	"DeepLearning handle a image, classification took "<< used <<" ms"<< endl;
		 //排序
		 Mat sort = argsort(preds);
		 //取top5
		 vector<int> inds;
		 for (int i=0; i< 5; i++){
		 	int ind = sort.at<int>(0, i);
		 	inds.push_back(ind);
		 }
		 //拼装返回数据
		 stringstream desc;
		 for(int i=0; i< inds.size(); i++){
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
				 "DeepLearning cv::imencode fail."<<endl;
		}
	}
	//这里初始化单实例
	DeepLearning* DeepLearning::instance = new DeepLearning();
	DeepLearning* DeepLearning::getInstance(){
		return instance;
	}
}