set(CMAKE_CXX_STANDARD 17)
set(cpprestsdk_DIR /usr/lib/x86_64-linux-gnu/cmake/)
set(yaml-cpp_DIR /home/daniel/yaml-cpp/build) # replace with the actual yaml-cpp build directory

cmake_minimum_required(VERSION 3.9)
project(main)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS random system thread filesystem chrono atomic date_time regex REQUIRED)

file(GLOB SOURCES
    "DeploymentHelper.cpp"
    "src/App/App.cpp"
    "src/App/App.hpp"
    "src/Config/Config.hpp"
    "src/Config/Config.cpp"
    "src/HTTP/Security/Security.cpp"
    "src/HTTP/Security/Security.hpp"
    "src/HTTP/Server/Server.cpp"
    "src/HTTP/Server/Server.hpp"
    "src/HTTP/ServerConfig/ServerConfig.cpp"
    "src/HTTP/ServerConfig/ServerConfig.hpp"
    "src/Logger/Logger.hpp"
    "src/Logger/Logger.cpp"
    "src/Step/Step.cpp"
    "src/Step/Step.hpp"
    "src/Utilities/Utilities.hpp"
    "src/Utilities/Utilities.cpp"
)

add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE
cpprestsdk::cpprest
  Boost::boost
  Boost::random
  Boost::system
  Boost::thread
  Boost::filesystem
  Boost::chrono
  Boost::atomic
  Boost::date_time
  Boost::regex
  yaml-cpp
  OpenSSL::SSL)
