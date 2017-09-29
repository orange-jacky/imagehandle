#cmake最低版本
cmake_minimum_required(VERSION 2.8)
#目录名称
project( iamgehandle )

#debug/release
set(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} -std=c++11 -o0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -o3 -Wall")
#添加编译参数
add_definitions("-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -std=c++11")

#设置编译使用cpu数量
set(NCPU 1)

# required for unit testing using CMake's ctest command
include(CTest)
enable_testing()

# required modules for our task
include(FindPkgConfig)
include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckIncludeFiles)
include(ExternalProject)
include(thirdparty/tinyxml2-master-source.cmake)
include(thirdparty/eigen_3.3.4.cmake)

#引入系统头文件
include_directories( /usr/local/include )

#编译项目子目录
add_subdirectory( thirdparty )
add_subdirectory( thrift )
add_subdirectory( handle )
add_subdirectory( util )
add_subdirectory( test )  #第三方依赖库测试模块

#编译可执行程序
add_executable(imagehandle main.cpp)
target_link_libraries(imagehandle 
		 handle
		 mythrift
		 util
)
