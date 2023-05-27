cmake_minimum_required(VERSION 3.12)
project(UserAPI)

set(CMAKE_CXX_STANDARD 17)
set(OPENSSL_USE_STATIC_LIBS TRUE)

set(OPENSSL_ROOT_DIR "/usr/local/Cellar/openssl@3/3.1.0")

find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

add_executable(UserAPI
        main.cpp
        user.h
        user.cpp
        utility.h
        utility.cpp
        user_repository.cpp
        user_service.cpp
        user_controller.cpp
        http_server.cpp
        default_user_service.cpp)

target_link_libraries(UserAPI PRIVATE OpenSSL::SSL cpprestsdk::cpprest)