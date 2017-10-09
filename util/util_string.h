#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <string>
#include <vector>

using namespace std;


namespace ImageHandle {
	namespace util{
		void splitStr(const string& str, const string& delims ,vector<string>& v);
	}
}

#endif