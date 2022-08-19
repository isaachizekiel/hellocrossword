cmake_minimum_required(VERSION 3.16)
project(hellocrossword)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# json dependency
find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
# if built with cmake
# CURL_INCLUDE_DIR and CURL_LIBRARIES are not required
# to link we use CURL::libcurl instead of CURL_LIBRARIES
find_package(CURL REQUIRED) 


include_directories(include ${CURL_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})

add_executable(${PROJECT_NAME} src/game.cpp src/gamestate.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
  nlohmann_json::nlohmann_json
  CURL::libcurl
  OpenSSL::SSL)

foreach(_target
    http_client_test)
  add_executable(test-${_target} "test/${_target}.cpp")
  target_link_libraries(test-${_target}    
    CURL::libcurl
    OpenSSL::SSL)  
endforeach()
