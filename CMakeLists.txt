set(CMAKE_CXX_STANDARD 17)
set(cpprestsdk_DIR /usr/lib/x86_64-linux-gnu/cmake/)
set(yaml-cpp_DIR /home/daniel/yaml-cpp/build)
#find_library(CPPREST_LIB cpprest)

#find_library(cpprest REQUIRED)
#find_package(cpprestsdk REQUIRED NAMES cpprestsdk cpprest)
#find_package(cpprestsdk REQUIRED)



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

#add_executable(deploypp DeploymentHelper.cpp)

add_executable(deploypp ${SOURCES})

#target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

target_link_libraries(deploypp PUBLIC
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

install(TARGETS deploypp
        RUNTIME
          DESTINATION "./"
        LIBRARY
          DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE
          DESTINATION "./archive")

set(CMAKE_INSTALL_PREFIX "./install")