#include "util_time.h"

namespace ImageHandle {
	namespace util{
		//获取当前时间的毫秒
		long GetMills()
		{
			struct timeval tp;
			gettimeofday(&tp, NULL);
			long ret =  tp.tv_sec * 1000 + tp.tv_usec / 1000;
			return ret;
		}
		//获取当前时间的时间戳
		string GetTimestamp()
		{
			time_t now;
			now = time(NULL);
			struct tm* t = localtime(&now);
			/*
			stringstream str;
			str<< t->tm_year + 1900<<"-";
			str<< t->tm_mon + 1<<"-";
			str<< t->tm_mday<< " ";
			str<< t->tm_hour<<":";
			str<< t->tm_min<<":";
			str<< t->tm_sec;
			return str.str();
			*/
			char buff[128];
			sprintf(buff, "%d-%02d-%02d %02d:%02d:%02d", 
				t->tm_year + 1900,
				t->tm_mon + 1,
				t->tm_mday,
				t->tm_hour,
				t->tm_min,
				t->tm_sec);
			return string(buff);
		}
	}
}