cmake_minimum_required(VERSION 3.14)
project(logs)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
  sensor_test

  core/sensor_test.cpp
  mock/mock_sensor.c

  ../include/safe_memory.h
  ../lib/safe_memory.o

  ../headers/sensor.h

  ../src/core/trigger/trigger.c
  ../src/core/sensor/sensor.c
)
target_link_libraries(
  sensor_test
  GTest::gtest_main
)

target_include_directories(sensor_test PRIVATE ../include)
target_include_directories(sensor_test PRIVATE ../headers)

include(GoogleTest)
gtest_discover_tests(sensor_test)