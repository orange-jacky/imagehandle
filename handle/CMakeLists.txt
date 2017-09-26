#引入opencv的头文件,库,包
find_package( OpenCV 3.3 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
link_directories( ${OpenCV_LIBRARY_DIRS} )

#目录
set(HANDLE_DIR ${CMAKE_SOURCE_DIR}/handle)
#源文件
set(HANDLE_SRC_FILES 
	${HANDLE_DIR}/colordescriptor.h
	${HANDLE_DIR}/colordescriptor.cpp
)
#生成库
add_library( handle STATIC ${HANDLE_SRC_FILES})
target_link_libraries( handle ${OpenCV_LIBS})