#ifndef UTIL_TIME_H
#define UTIL_TIME_H

#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <time.h> 
#include <stdio.h>

using namespace std;

namespace ImageHandle {
	namespace util{
		long GetMills();
		string GetTimestamp();
	}
}

#endif