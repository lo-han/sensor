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

  tests/core/safe_memory_test.cpp
  tests/core/sensor_trigger_test.cpp
  infra/mock/mock_sensor.c

  core/memory/safe_memory.h
  core/memory/safe_memory.c
  core/trigger/trigger.h
  core/trigger/trigger.c
  core/sensor/sensor.h
  core/sensor/sensor.c
)
target_link_libraries(
  sensor_test
  GTest::gtest_main
)

target_include_directories(sensor_test PRIVATE core/memory)
target_include_directories(sensor_test PRIVATE core/trigger)
target_include_directories(sensor_test PRIVATE core/sensor)

include(GoogleTest)
gtest_discover_tests(sensor_test)