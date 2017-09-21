#cmake最低版本
cmake_minimum_required(VERSION 2.8)
#目录名称
project( iamgehandle )

#debug/release
set(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} -std=c++11 -o0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -o3 -Wall")

#添加编译参数
add_definitions("-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -std=c++11")

# cmake可以使用pkg-config
include(FindPkgConfig)

#引入系统头文件
include_directories(
	/usr/local/include
)

#第三方库
set(THRIDPARTY_LIB_PATH "" ) #路径
set(THRIDPARTY_LIB "")      #库名称

#编译项目子目录
add_subdirectory( thrift )
add_subdirectory( handle )

#编译可执行程序
add_executable(imagehandle main.cpp)
target_link_libraries(imagehandle 
		 ${THRIDPARTY_LIB}
		 MyHandle
		 MyThrift
)
