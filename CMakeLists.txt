cmake_minimum_required(VERSION 3.10)
project(sql_pool)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/)

find_package(Threads REQUIRED)
find_package(FreeTDS REQUIRED)

include_directories(include)

LIST(APPEND srcs
  src/SqlClient.cpp
  src/SqlConnection.cpp
  src/SqlConnectionFactory.cpp
  src/SqlParams.cpp
  )


# Define library
add_library(sql_pool STATIC ${srcs})

target_include_directories(sql_pool PUBLIC ${PROJECT_SOURCE_DIR}/include)
