#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <iostream>
#include <sstream>
#include <tinyxml2.h>

using namespace tinyxml2;
using namespace std;

namespace ImageHandle {
	namespace util{
		class C {
		public:
			string host;
			string    port;
			//deep learning
			string dp_prototxt;
			string dp_mode;
			string dp_labels;
			//object dection
			string od_prototxt;
			string od_mode;
			string od_labels;
		};
		class Configure{
		public:
			C c;
		private:
			static Configure* instance;
		public:
			int Parse(const char* filename);
			string String();
			//单实例
			static Configure* getInstance();
		private:
			Configure();
			~Configure(){};
			//把复制构造函数和=操作符也设为私有,防止被复制
			Configure(const Configure&);
			Configure& operator=(const Configure&);
		};
	}
}
#endif
