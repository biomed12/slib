cmake_minimum_required(VERSION 3.14)

project(endonezya-kaplan-development LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

include_directories(gtest_gmock)

add_executable(endonezya-kaplan-development
  main.cpp
  slib/s_port_connector.hpp
  slib/s_serial_port.hpp
  slib/s_timer.hpp
  slib/s_io.hpp
  slib/s_tickable.hpp
  slib/s_tickable.cpp
  slib/s_runnable.hpp
  slib/s_runnable.cpp
  slib/s_util.hpp
  slib/s_service.hpp
  gtest_gmock/gmock/gmock.h
  gtest_gmock/gtest/gtest.h
  gtest_gmock/gmock-gtest-all.cc
  tests/s_timer_test.cpp
  tests/s_serial_port_test.cpp
  tests/s_port_connector_test.cpp
  tests/s_io_test.cpp
  tests/s_util_test.cpp
  tests/s_service_test.cpp
  tests/s_runnable_test.cpp
  utils/xcore_la_154_protocol.hpp
)
target_link_libraries(endonezya-kaplan-development Qt${QT_VERSION_MAJOR}::Core)
