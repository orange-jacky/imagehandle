1.安装thrift
	请参考官网安装,
	如果是centos系统,可以使用 yum install thrift*

2.安装opencv3.3.0
	请参考官网安装
		http://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html
	如果是centos系统,可以使用 yum install opencv*
		但是yum安装的opencv不一定是3.3.0, 如果不是,请参考上面链接安装

3.编译thrift文件
	进入目录thrift,找到ImageHandle.thrift文件
	执行
	thrift --gen cpp ImageHandle.thrift
	thrift目录里多了gen-cpp 目录

4.覆盖文件
	把thirft/gen-cpp目录里的下面文件 复制到 imagehandle目录下
	Handler.h
	Handler.cpp
	ImageHandle_constants.h
	ImageHandle_constants.cpp
	ImageHandle_types.h
	ImageHandle_types.cpp

5.编译
编译出可执行程序命令
g++ -std=c++11 -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H -Wall -I/usr/local/include *.cpp `pkg-config --cflags --libs opencv thrift` -o imagehandle


mkdir build
cd build
cmake ..
make


6.启动服务
./start.sh