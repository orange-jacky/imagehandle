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
			XMLElement* host = doc.FirstChildElement("root")->FirstChildElement("server")->FirstChildElement("host");
			c.host = string(host->GetText());	
	   		XMLElement* port = doc.FirstChildElement("root")->FirstChildElement("server")->FirstChildElement("port");
			c.port = string(port->GetText());
	    	return 0;
		}
		string  Configure::String(){
			stringstream str;
			str<<"server:{host:"<<c.host<<",port:"<<c.port<<"} ";
			return str.str();
		}
		//这里初始化单实例
		Configure* Configure::instance = new Configure();
		Configure* Configure::getInstance(){
			return instance;
		}
	}
}
