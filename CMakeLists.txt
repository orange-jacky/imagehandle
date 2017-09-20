cmake_minimum_required(VERSION 2.8)
project( iamgehandle )
find_package( OpenCV 3.3 REQUIRED )


include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB cppfile
    "*.h"
    "*.cpp"
)
add_executable( iamgehandle ${cppfile} )
target_link_libraries( iamgehandle ${OpenCV_LIBS} )
