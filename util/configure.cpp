#include "configure.h"

namespace ImageHandle {
	namespace util{
		Configure::Configure(){

		}
		Configure::Configure(const Configure&){

		}
		Configure& Configure::operator=(const Configure&){

		}
		int Configure::Parse(const char* filename){
			XMLDocument doc;
			doc.LoadFile(filename);
			if(doc.ErrorID() != 0) return doc.ErrorID();  // 如果无法读取文件，则返回
			//server
			XMLElement* host = doc.FirstChildElement("root")->FirstChildElement("server")->FirstChildElement("host");
			c.host = string(host->GetText());	
	   		XMLElement* port = doc.FirstChildElement("root")->FirstChildElement("server")->FirstChildElement("port");
			c.port = string(port->GetText());
			
			//deep_learning
			XMLElement* prototxt = doc.FirstChildElement("root")->FirstChildElement("deep_learning")->FirstChildElement("protoext");
			c.dp_prototxt = string(prototxt->GetText());	
	   		XMLElement* mode = doc.FirstChildElement("root")->FirstChildElement("deep_learning")->FirstChildElement("mode");
			c.dp_mode = string(mode->GetText());
	   		XMLElement* labels = doc.FirstChildElement("root")->FirstChildElement("deep_learning")->FirstChildElement("labels");
			c.dp_labels = string(labels->GetText());
			
			//object_dection
			XMLElement* prototxt1 = doc.FirstChildElement("root")->FirstChildElement("object_detection")->FirstChildElement("protoext");
			c.od_prototxt = string(prototxt1->GetText());	
	   		XMLElement* mode1 = doc.FirstChildElement("root")->FirstChildElement("object_detection")->FirstChildElement("mode");
			c.od_mode = string(mode1->GetText());
	   		XMLElement* labels1= doc.FirstChildElement("root")->FirstChildElement("object_detection")->FirstChildElement("labels");
			if (labels1->GetText()){
				c.od_labels = string(labels1->GetText());
			}
			
	    	return 0;
		}
		string  Configure::String(){
			stringstream str;
			str<<"server:{host:"<<c.host<<",port:"<<c.port<<"} "<<endl;
			str<<"deeplearning:{prototxt:"<<c.dp_prototxt <<", mode:"<< c.dp_mode<<", lables:"<<c.dp_labels<<"} "<<endl;
			return str.str();
		}
		//这里初始化单实例
		Configure* Configure::instance = new Configure();
		Configure* Configure::getInstance(){
			return instance;
		}
	}
}