#引入thrift的头文件,库,包
pkg_check_modules(THRIFT thrift)
include_directories( ${THRIFT_INCLUDE_DIRS} )
link_directories( ${THRIFT_LIBRARY_DIRS} )
set(THRIFT_LIBS thrift)

#message(STATUS "${THRIFT_INCLUDE_DIRS} ${THRIFT_LIBRARY_DIRS} ${THRIFT_LIBS}")

#thrift
message(STATUS "Use thrift file to generate cpp code")

#目录
set(THRIFT_DIR ${CMAKE_SOURCE_DIR}/thrift)
set(THRIFT_FILE ${THRIFT_DIR}/ImageHandle.thrift)
set(THRIFT_OUTPUT_DIR ${THRIFT_DIR})

#用thrift文件生成c++服务端代码
exec_program("thrift --gen cpp  -o ${THRIFT_OUTPUT_DIR} ${THRIFT_FILE}" OUTPUT_VARIABLE a)

#源文件
set(THRIFT_SRC_FILES 
	${THRIFT_OUTPUT_DIR}/gen-cpp/ImageHandle_constants.h
	${THRIFT_OUTPUT_DIR}/gen-cpp/ImageHandle_constants.cpp
	${THRIFT_OUTPUT_DIR}/gen-cpp/ImageHandle_types.h
	${THRIFT_OUTPUT_DIR}/gen-cpp/ImageHandle_types.cpp
	${THRIFT_OUTPUT_DIR}/gen-cpp/Handler.h
	${THRIFT_OUTPUT_DIR}/gen-cpp/Handler.cpp
)

#生成库
add_library( mythrift STATIC ${THRIFT_SRC_FILES})
target_link_libraries(mythrift ${THRIFT_LIBS})
