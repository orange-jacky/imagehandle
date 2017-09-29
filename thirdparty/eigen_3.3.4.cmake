#eigen不需要编译,直接解压就可以使用

set(EIGEN_PREFIX eigen)
set(EIGEN_URL ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/eigen_3.3.4.tar.bz2)
set(EIGEN_URL_MD5 a7aab9f758249b86c93221ad417fbe18)

ExternalProject_Add(${EIGEN_PREFIX}
    PREFIX ${EIGEN_PREFIX}
    URL ${EIGEN_URL}
    URL_MD5 ${EIGEN_URL_MD5}
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ""
    CMAKE_GENERATOR ""
    CMAKE_COMMAND ""
 	BUILD_COMMAND ""
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
    LOG_DOWNLOAD 1
    LOG_BUILD 1
)

ExternalProject_Get_Property(${EIGEN_PREFIX} PREFIX)
ExternalProject_Get_Property(${EIGEN_PREFIX} SOURCE_DIR)

# set the include directory variable and include it
set(EIGEN_INCLUDE_DIRS ${SOURCE_DIR})
include_directories(${EIGEN_INCLUDE_DIRS})

link_directories(${SOURCE_DIR})
set(EIGEN_LIBRARY_DIRS ${SOURCE_DIR})
#set(EIGEN_LIBS eigen)

message(STATUS "lib and header file directory of ${SOURCE_DIR}")
#message(STATUS "library ${EIGEN_LIBS}")
