cmake_minimum_required(VERSION 3.1)
project(WorkInitClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Client/Client.cpp src/Client/Credential.cpp)

link_directories(/usr/local/lib)
link_directories(/usr/local)
link_directories(/usr/lib64/)
link_directories(/usr/local/opt/openssl/lib)
include_directories(/usr/local/opt/openssl/include)

find_library(LIB_OPENSSL ssl)
find_library(LIB_CRYPTO  crypto)

add_executable(work_init_c_run ${SOURCE_FILES})

target_link_libraries(work_init_c_run ${LIB_OPENSSL} ${LIB_CRYPTO})

include_directories(src)

link_directories(/usr/local/lib)
link_directories(/usr/local)