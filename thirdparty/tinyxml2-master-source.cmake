# tinyxml2, this library is used for XML IO
#直接在源目录使用make编译,不执行cmake
set(TINYXML2_PREFIX tinyxml2-master)
set(TINYXML2_URL ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/tinyxml2-master.zip)
set(TINYXML2_URL_MD5 51eacf693007b789ab61b785aa0619b4)

ExternalProject_Add(${TINYXML2_PREFIX}
    PREFIX ${TINYXML2_PREFIX}
    URL ${TINYXML2_URL}
    URL_MD5 ${TINYXML2_URL_MD5}
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ""
    CMAKE_GENERATOR ""
    CMAKE_COMMAND ""
 	BUILD_COMMAND make -j${NCPU}
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
    LOG_DOWNLOAD 1
    LOG_BUILD 1
)

ExternalProject_Get_Property(${TINYXML2_PREFIX} PREFIX)
ExternalProject_Get_Property(${TINYXML2_PREFIX} SOURCE_DIR)

# set the include directory variable and include it
set(TINYXML2_INCLUDE_DIRS ${SOURCE_DIR})
include_directories(${TINYXML2_INCLUDE_DIRS})

link_directories(${SOURCE_DIR})
set(TINYXML2_LIBRARY_DIRS ${SOURCE_DIR})
set(TINYXML2_LIBS tinyxml2)

message(STATUS "lib and header file directory of ${SOURCE_DIR}")
message(STATUS "library ${TINYXML2_LIBS}")


