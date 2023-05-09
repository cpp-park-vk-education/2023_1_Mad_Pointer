set(CMAKE_CXX_STANDARD 20)

cmake_minimum_required(VERSION 3.8)
project(my_project)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread -lpthread -lm")

set(BOOST_ROOT /usr/include/boost)
include_directories(/usr/include/boost)
include_directories(/usr/include/openssl)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Threads REQUIRED)

add_executable(client_websocket game/client/main.cpp)

add_executable(server_websocket game/server/main.cpp)

target_link_libraries(client_websocket PRIVATE OpenSSL::SSL OpenSSL::Crypto Boost::system Threads::Threads )
target_link_libraries(server_websocket PRIVATE OpenSSL::SSL OpenSSL::Crypto Boost::system Threads::Threads )


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(Test game/client/main.cpp)
target_link_libraries(Test ${SDL2_LIBRARIES})