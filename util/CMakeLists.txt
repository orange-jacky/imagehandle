#目录
set(UTIL_DIR ${CMAKE_SOURCE_DIR}/util)
#源文件
set(UTIL_SRC_FILES 
	${UTIL_DIR}/configure.cpp
)

#生成库
add_library( util STATIC ${UTIL_SRC_FILES})
add_dependencies(util ${TINYXML2_PREFIX})   #util库依赖tinyxml2库,tinyxml2必须先编译
target_link_libraries(util ${TINYXML2_LIBS})
