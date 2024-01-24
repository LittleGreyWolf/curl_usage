#指定版本
cmake_minimum_required(VERSION 3.10)
 
#指定工程名称
project(res)
 
#设置变量的值
set(SRC ${PROJECT_SOURCE_DIR}/src/main.cpp) 
 
#指定头文件位置
include_directories(${PROJECT_SOURCE_DIR}/libcurl/include)
 
#生成可执行文件
add_executable(res ${SRC})

IF(WIN32)
	target_link_libraries(res ${PROJECT_SOURCE_DIR}/libcurl/vc_x86/libcurl.lib)
ELSEIF(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-rpath=../libcurl/gcc_x64:.")
	target_link_libraries(res ${PROJECT_SOURCE_DIR}/libcurl/gcc_x64/libcurl.so.4.8.0)
ENDIF()