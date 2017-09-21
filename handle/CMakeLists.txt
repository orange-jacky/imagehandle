#引入opencv的头文件,库,包
find_package( OpenCV 3.3 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(THRIDPARTY_LIB_PATH ${THRIDPARTY_LIB_PATH} ${OpenCV_LIBRARY_DIRS} PARENT_SCOPE)
set(THRIDPARTY_LIB ${THRIDPARTY_LIB} ${OpenCV_LIBS} PARENT_SCOPE)

#目录
set(HANDLE_DIR ${CMAKE_SOURCE_DIR}/handle)
#源文件
set(HANDLE_SRC_FILES 
	${HANDLE_DIR}/colordescriptor.h
	${HANDLE_DIR}/colordescriptor.cpp
)
#生成库
add_library( MyHandle STATIC ${HANDLE_SRC_FILES})

