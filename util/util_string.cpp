#include "util_string.h"


namespace ImageHandle {
	namespace util{
		void splitStr(const string& str, const string& delims ,vector<string>& v)
		{
		    std::size_t current, previous = 0;
		    current = str.find_first_of(delims);
		    while (current != std::string::npos) {
		        v.push_back(str.substr(previous, current - previous));
		        previous = current + delims.length();;
		        current = str.find_first_of(delims, previous);
		    }
		    v.push_back(str.substr(previous, current - previous));
		}
	}
}