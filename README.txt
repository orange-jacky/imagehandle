1.安装thrift
	请参考官网安装,
	如果是centos系统,可以使用 yum install thrift*

2.安装opencv3.3.0
	请参考官网安装
		http://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html
	如果是centos系统,可以使用 yum install opencv*
		但是yum安装的opencv不一定是3.3.0, 如果不是,请参考上面链接安装
3.编译
	mkdir build
	cd build
	cmake ..
	make
4.启动服务
./start.sh


模型文件和thridparty依赖库,都比较大,就不上传到github上了,有需要的,请给我发邮件,单独发给你.
email:
	orange.jackylee@gmail.com